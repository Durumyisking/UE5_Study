// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
//#include "MyEnhancedInputComponent.generated.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
	: mCamera(nullptr)
	, mSpringArm(nullptr)
	, mInputMappingContext(nullptr)
	, mAction_MoveFoward(nullptr)
	, mAction_MoveBack(nullptr)
	, mAction_MoveSide(nullptr)
	, mAction_Jump(nullptr)
	, mAction_Run(nullptr)
	, mAction_Rotate(nullptr)
	, mMoveFowardSpeed(0.5f)
	, mMoveBackSpeed(0.25f)
	, mMoveSideSpeed(0.5f)
	, mState{}
	, mMoveDir{}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mSpringArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 500.f;
	mSpringArm->TargetOffset = { 0.f, 0.f, 100.f };

	auto movementComponent = Cast< UCharacterMovementComponent>(GetCharacterMovement());
	if (movementComponent)
	{
		movementComponent->MaxWalkSpeed = 300.f;
		movementComponent->GroundFriction = 16.f;
	}

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 플레이어 컨트롤러 획득
	auto playerController = Cast<APlayerController>(GetController());

	if (nullptr != playerController)
	{
		// LocalPlayer의 향상된입력 얻기
		auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		// Add the input mapping context

		if (nullptr != eiSubsystem)
		{
			eiSubsystem->AddMappingContext(mInputMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PrintLogByState();
	PrintLogByMoveDir();

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

		playerEIcomponent->BindAction(mAction_MoveFoward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveFoward);
		playerEIcomponent->BindAction(mAction_MoveFoward, ETriggerEvent::Completed, this, &APlayerCharacter::MoveFoward);

		playerEIcomponent->BindAction(mAction_MoveBack, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveBack);
		playerEIcomponent->BindAction(mAction_MoveBack, ETriggerEvent::Completed, this, &APlayerCharacter::MoveBack);

		playerEIcomponent->BindAction(mAction_MoveSide, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveSide);
		playerEIcomponent->BindAction(mAction_MoveSide, ETriggerEvent::Completed, this, &APlayerCharacter::MoveSide);

		playerEIcomponent->BindAction(mAction_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

		playerEIcomponent->BindAction(mAction_Run, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);
		playerEIcomponent->BindAction(mAction_Run, ETriggerEvent::Completed, this, &APlayerCharacter::Run);

		playerEIcomponent->BindAction(mAction_Rotate, ETriggerEvent::Triggered, this, &APlayerCharacter::Rotate);

	}

}

void APlayerCharacter::Idle(const FInputActionValue& value)
{	
	if (mState.none())
	{
		mState[static_cast<UINT>(EPlayerState::Idle)] = true;
	}
}

void APlayerCharacter::MoveFoward(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		AddMovementInput(GetActorForwardVector(), mMoveFowardSpeed);
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
			mMoveDir[static_cast<UINT>(EMoveDir::S)] = true;
			mMoveDir[static_cast<UINT>(EMoveDir::A)] = false;
		}
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Move)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::D)] = false;
		mMoveDir[static_cast<UINT>(EMoveDir::A)] = false;
	}
	
}

void APlayerCharacter::Run(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		if (mMoveDir[static_cast<UINT>(EMoveDir::W)])
		{
			mState[static_cast<UINT>(EPlayerState::Run)] = true;
			mMoveFowardSpeed = 1.f;
			mMoveSideSpeed = 0.25f;
		}
		else
		{
			mState[static_cast<UINT>(EPlayerState::Run)] = false;
			mMoveFowardSpeed = 0.5f;
			mMoveSideSpeed = 0.5f;
		}
	}
	else
	{
		mState[static_cast<UINT>(EPlayerState::Run)] = false;
		mMoveFowardSpeed = 0.5f;
	}
}

void APlayerCharacter::Rotate(const FInputActionValue& value)
{
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

