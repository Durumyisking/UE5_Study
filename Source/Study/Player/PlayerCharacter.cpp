// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
//#include "MyEnhancedInputComponent.generated.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PlayerAnimInstance.h"
#include "../UI/CrossHairWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	: mCamera(nullptr)
	, mSpringArm(nullptr)
	, mInputMappingContext(nullptr)
	, mAction_Idle(nullptr)
	, mAction_MoveForward(nullptr)
	, mAction_MoveBack(nullptr)
	, mAction_MoveSide(nullptr)
	, mAction_Jump(nullptr)
	, mAction_Run(nullptr)
	, mAction_Rotate(nullptr)
	, mAction_Shoot(nullptr)
	, mAction_Zoom(nullptr)
	, mAniminstance(nullptr)
	, mCrosshair(nullptr)
	, mUpperBodyMontageMap{}
	, mMoveForwardSpeed(0.5f)
	, mMoveBackSpeed(0.25f)
	, mMoveSideSpeed(0.5f)
	, mState{}
	, mMoveDir{}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컨트롤러(마우스)를 사용한 캐릭터의 회전을 막습니다.
	bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mSpringArm->SetupAttachment(RootComponent);
	mSpringArm->TargetArmLength = 300.f;
	mSpringArm->bUsePawnControlRotation = true;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);
	mCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	mCamera->AddLocalOffset({ 20.f, 40.f, 65.f });

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->GroundFriction = 16.f;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Script/Engine.CurveFloat'/Game/MyContents/ETC/ZoomCurve.ZoomCurve'"));
	if (Curve.Succeeded())
	{
		mZoomCurve = Curve.Object;
	}


	//static ConstructorHelpers::FClassFinder<UCrossHairWidget> CrosshairWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContents/UI/UI_Crosshair.UI_Crosshair'"));

	//if (CrosshairWidget.Succeeded())
	//{
	//	mCrosshair = CreateWidget<UCrossHairWidget>(GetWorld(), CrosshairWidget)
	//}


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 컨트롤러 획득
	if (auto playerController = Cast<APlayerController>(GetController()))
	{
		// LocalPlayer의 향상된입력 얻기
		if (auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			eiSubsystem->AddMappingContext(mInputMappingContext, 0);
		}
	}


	ZoomTimelineSetting();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTimeline.TickTimeline(DeltaTime);
	//PrintLogByState();
	//PrintLogByMoveDir();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindActions(PlayerInputComponent);
}

void APlayerCharacter::BindActions(UInputComponent* PlayerInputComponent)
{
	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (nullptr != playerEIcomponent)
	{
		//Bind Move() to the mapping
		//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
		//ETriggerEvent is an enum, where Triggered means "button is held down".
		playerEIcomponent->BindAction(mAction_Idle, ETriggerEvent::None, this, &APlayerCharacter::Idle);

		playerEIcomponent->BindAction(mAction_MoveForward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		playerEIcomponent->BindAction(mAction_MoveForward, ETriggerEvent::Completed, this, &APlayerCharacter::MoveForward);

		playerEIcomponent->BindAction(mAction_MoveBack, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveBack);
		playerEIcomponent->BindAction(mAction_MoveBack, ETriggerEvent::Completed, this, &APlayerCharacter::MoveBack);

		playerEIcomponent->BindAction(mAction_MoveSide, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveSide);
		playerEIcomponent->BindAction(mAction_MoveSide, ETriggerEvent::Completed, this, &APlayerCharacter::MoveSide);

		//playerEIcomponent->BindAction(mAction_Jump, ETriggerEvent::Started, this, &APlayerCharacter::Jump);
		//playerEIcomponent->BindAction(mAction_Jump, ETriggerEvent::Completed, this, &APlayerCharacter::StopJumping);

		playerEIcomponent->BindAction(mAction_Run, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);
		playerEIcomponent->BindAction(mAction_Run, ETriggerEvent::Completed, this, &APlayerCharacter::Run);

		playerEIcomponent->BindAction(mAction_Rotate, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);

		playerEIcomponent->BindAction(mAction_Shoot, ETriggerEvent::Triggered, this, &APlayerCharacter::Shoot);
		playerEIcomponent->BindAction(mAction_Shoot, ETriggerEvent::Completed, this, &APlayerCharacter::Shoot);

		playerEIcomponent->BindAction(mAction_Zoom, ETriggerEvent::Started, this, &APlayerCharacter::ZoomInStart);
		playerEIcomponent->BindAction(mAction_Zoom, ETriggerEvent::Triggered, this, &APlayerCharacter::ZoomIn);
		playerEIcomponent->BindAction(mAction_Zoom, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomOut);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' EnhancedComponent 초기화 실패!"), *GetNameSafe(this));
	}
}

void APlayerCharacter::Idle(const FInputActionValue& value)
{	
	if (mState.none())
	{
		mState[static_cast<UINT>(EPlayerState::Idle)] = true;
	}
}

void APlayerCharacter::MoveForward(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		AddMovementInput(GetActorForwardVector(), mMoveForwardSpeed);
		mState[static_cast<UINT>(EPlayerState::Idle)] = false;
		mState[static_cast<UINT>(EPlayerState::Move)] = true;
		mMoveDir[static_cast<UINT>(EMoveDir::W)] = true;
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Move)] = false;
		mState[static_cast<UINT>(EPlayerState::Run)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::W)] = false;
	}
}

void APlayerCharacter::MoveBack(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		AddMovementInput(-GetActorForwardVector(), mMoveBackSpeed);
		mState[static_cast<UINT>(EPlayerState::Idle)] = false;
		mState[static_cast<UINT>(EPlayerState::Move)] = true;
		mState[static_cast<UINT>(EPlayerState::Run)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::S)] = true;
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Move)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::S)] = false;
	}
}

void APlayerCharacter::MoveSide(const FInputActionValue& value)
{
	float side = value.Get<float>();

	if (0.f != side)
	{
		AddMovementInput(side * GetActorRightVector(), mMoveSideSpeed);
		mState[static_cast<UINT>(EPlayerState::Idle)] = false;
		mState[static_cast<UINT>(EPlayerState::Move)] = true;

		if (side > 0.f)
		{
			mMoveDir[static_cast<UINT>(EMoveDir::D)] = true;
			mMoveDir[static_cast<UINT>(EMoveDir::A)] = false;
		}
		else
		{
			mMoveDir[static_cast<UINT>(EMoveDir::A)] = true;
			mMoveDir[static_cast<UINT>(EMoveDir::D)] = false;
		}
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Move)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::D)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::A)] = false;
	}
	
}

void APlayerCharacter::Jump()
{
	Super::Jump();
	mState.reset();
	mState[static_cast<UINT>(EPlayerState::Jump)] = true;
}

void APlayerCharacter::StopJumping()
{
	Super::StopJumping();
	mState.reset();
	mState[static_cast<UINT>(EPlayerState::Jump)] = false;
}

void APlayerCharacter::Run(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		if (mMoveDir[static_cast<UINT>(EMoveDir::W)])
		{
			mState[static_cast<UINT>(EPlayerState::Run)] = true;
			mMoveForwardSpeed = 1.f;
			mMoveSideSpeed = 0.25f;

			mAniminstance->SetZoomOff();

		}
		else
		{
			mState[static_cast<UINT>(EPlayerState::Run)] = false;
			mMoveForwardSpeed = 0.5f;
			mMoveSideSpeed = 0.5f;
		}
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Run)] = false;
		mMoveForwardSpeed = 0.5f;
		mMoveSideSpeed = 0.5f;
	}
}

void APlayerCharacter::Rotate(const FInputActionValue& value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Shoot(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		if(!mState[static_cast<UINT>(EPlayerState::Run)])
		{
			// 줌 Start 몽타주 재생중이면
			if (!mAniminstance->Montage_IsPlaying(mUpperBodyMontageMap["ZoomStart"]))
			{
				mAniminstance->PlayMontage(mUpperBodyMontageMap["Shoot"]);
				mState[static_cast<UINT>(EPlayerState::Idle)] = false;
				mState[static_cast<UINT>(EPlayerState::Shoot)] = true;
			}
		}
	}

}

void APlayerCharacter::ZoomInStart()
{
	mTimeline.ReverseFromEnd();
}

void APlayerCharacter::ZoomIn()
{	
	if (!mState[static_cast<UINT>(EPlayerState::Run)])
	{
		if (!mAniminstance->IsZooming())
		{
			mState[static_cast<UINT>(EPlayerState::Zoom)] = true;
			mAniminstance->PlayMontage(mUpperBodyMontageMap["ZoomStart"]);
		}
	}
}
void APlayerCharacter::ZoomOut()
{
	mState[static_cast<UINT>(EPlayerState::Zoom)] = false;
	mAniminstance->SetZoomOff();
	mAniminstance->StopMontage(mUpperBodyMontageMap["ZoomStart"], 0.5f);
	mTimeline.PlayFromStart();
}

void APlayerCharacter::ZoomTimelineSetting()
{
	mTimeline = {};
	FOnTimelineFloat callback = {};
	callback.BindUFunction(this, "CameraZoomInOut");
	mTimeline.AddInterpFloat(mZoomCurve, callback);
	mTimeline.SetTimelineLength(0.2f);
}

void APlayerCharacter::CameraZoomInOut(float value)
{
	//LOG(TEXT("armlength : %s"), mSpringArm->TargetArmLength);
	mSpringArm->TargetArmLength = value;
}

void APlayerCharacter::SetPlayerSingleState(EPlayerState state)
{
	mState.reset();
	mState[static_cast<UINT>(state)] = true;
}

void APlayerCharacter::PrintLogByState()
{
	if (mState[static_cast<UINT>(EPlayerState::Idle)])
	{
		PrintViewport(0.5f, FColor::Red, "State : Idle");
	}
	if (mState[static_cast<UINT>(EPlayerState::Move)])
	{
		PrintViewport(0.5f, FColor::Red, "State : Move");
	}
	if (mState[static_cast<UINT>(EPlayerState::Run)])
	{
		PrintViewport(0.5f, FColor::Red, "State : Run");
	}
	if (mState[static_cast<UINT>(EPlayerState::Shoot)])
	{
		PrintViewport(0.5f, FColor::Red, "State : Shoot");
	}
	if (mAniminstance->IsZooming())
	{
		PrintViewport(0.5f, FColor::Red, "State : Zoom");
	}

}

void APlayerCharacter::PrintLogByMoveDir()
{
	if (mMoveDir[static_cast<UINT>(EMoveDir::W)])
	{
		PrintViewport(0.5f, FColor::Red, "Dir : W");
	}
	if (mMoveDir[static_cast<UINT>(EMoveDir::S)])
	{
		PrintViewport(0.5f, FColor::Red, "Dir : S");
	}
	if (mMoveDir[static_cast<UINT>(EMoveDir::A)])
	{
		PrintViewport(0.5f, FColor::Red, "Dir : A");
	}
	if (mMoveDir[static_cast<UINT>(EMoveDir::D)])
	{
		PrintViewport(0.5f, FColor::Red, "Dir : D");
	}
}

