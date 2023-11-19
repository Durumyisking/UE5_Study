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
	, mAction_Move(nullptr)
	, mAction_Jump(nullptr)
	, mAction_Run(nullptr)
	, mMovementSpeed(1.f)
	, mState{}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	mCamera->SetupAttachment(mSpringArm);

	mSpringArm->TargetArmLength = 500.f;
	mSpringArm->TargetOffset = { 0.f, 0.f, 100.f };
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
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

	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (nullptr != playerEIcomponent)
	{
		//Bind Move() to the mapping
		//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
		//ETriggerEvent is an enum, where Triggered means "button is held down".
		playerEIcomponent->BindAction(mAction_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		playerEIcomponent->BindAction(mAction_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		playerEIcomponent->BindAction(mAction_Run, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);

	}
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	auto playerController = Cast<APlayerController>(GetController());
	const FVector3d moveVector = value.Get<FVector3d>();

	if (nullptr != playerController)
	{
		mState[static_cast<UINT>(PlayerState::Move)] = true;

		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yaw(0.f, rotation.Yaw, 0.f);
		const FVector fowardDirection = FRotationMatrix(yaw).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(yaw).GetUnitAxis(EAxis::Y);


		AddMovementInput(fowardDirection, moveVector.X * mMovementSpeed);
		AddMovementInput(rightDirection, moveVector.Y );
	}


}

void APlayerCharacter::Run(const FInputActionValue& value)
{
	const bool input = value.Get<bool>();

	if (input)
	{
		mMovementSpeed = 10.5f;
		mState[static_cast<UINT>(PlayerState::Run)] = true;
	}
	else
	{
		mMovementSpeed = 1.f;
		mState[static_cast<UINT>(PlayerState::Run)] = false;
	}
}

void APlayerCharacter::SetPlayerSingleState(PlayerState state)
{
	mState.reset();
	mState[static_cast<UINT>(state)] = true;
}

