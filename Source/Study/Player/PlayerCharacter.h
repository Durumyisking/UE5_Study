// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class STUDY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	//UENUM(BlueprintType)
	enum class PlayerState : uint8
	{
		Idle,
		Move,
		Jump,
		Run,
		End,
	};

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* mInputMappingContext;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* mAction_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* mAction_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* mAction_Run;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* mAction_Rotate;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Actions
	void Move(const struct FInputActionValue& value);
	void Run(const FInputActionValue& value);
	void Rotate(const FInputActionValue& value);

	bool GetPlayerState(PlayerState state) const { return mState[static_cast<UINT>(state)]; }
	void SetPlayerState(PlayerState state, bool value) { mState[static_cast<UINT>(state)] = value; }
	void SetPlayerSingleState(PlayerState state);

private:
	float mMovementSpeed;

	std::bitset< static_cast<UINT>(PlayerState::End)> mState;

};
