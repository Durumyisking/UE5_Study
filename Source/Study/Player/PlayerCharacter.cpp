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

	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	//Add the input mapping context
	eiSubsystem->AddMappingContext(mInputMappingContext, 0);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(mAction_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	const FVector3d moveVector = value.Get<FVector3d>();

	AddMovementInput({ 1.f, 0.f, 0.f }, 10.f);

	UE_LOG(LogTemp, Warning, TEXT("Test log"));

}

