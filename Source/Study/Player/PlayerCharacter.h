// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Components/TimeLineComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class STUDY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APlayerCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetAnimInstance(class UPlayerAnimInstance* animInstance) { mAniminstance = animInstance; }

	// Actions
	void BindActions(UInputComponent* PlayerInputComponent);

	void Idle(const struct FInputActionValue& value);

	void MoveForward(const struct FInputActionValue& value);
	void MoveBack(const struct FInputActionValue& value);
	void MoveSide(const struct FInputActionValue& value);

	virtual void Jump		();
	virtual void StopJumping();


	void Run(const FInputActionValue& value);
	void Rotate(const FInputActionValue& value);

	void Shoot(const FInputActionValue& value);
	void ZoomInStart();
	void ZoomIn();
	void ZoomOut();

	void ZoomTimelineSetting();

	UFUNCTION()
	void CameraZoomInOut(float value);

	bool GetPlayerState(EPlayerState state) const { return mState[static_cast<UINT>(state)]; }
	void SetPlayerState(EPlayerState state, bool value) { mState[static_cast<UINT>(state)] = value; }
	void SetPlayerSingleState(EPlayerState state);

	bool GetMoveDir(EMoveDir dir) const { return mMoveDir[static_cast<UINT>(dir)]; }
	void SetMoveDir(EMoveDir dir, bool value) { mMoveDir[static_cast<UINT>(dir)] = value; }

	const UAnimMontage* FindAnimMontage(const FString& key) { return mUpperBodyMontageMap[key]; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetSprintArm() const { return mSpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return mCamera; }

	void SetMainWidget(class UMainWidget* mainWidget) { mMainWidget = mainWidget; }

	// state Log
	void PrintLogByState();
	void PrintLogByMoveDir();

	bool IsShooting() const { return mState[static_cast<UINT>(EPlayerAnimState::Shoot)]; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* mCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* mSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* mInputMappingContext;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction* mAction_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_MoveForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_MoveBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_MoveSide;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_Jump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_Run;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* mAction_Zoom;

	// Montage
	UPlayerAnimInstance* mAniminstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<FString, UAnimMontage*> mUpperBodyMontageMap;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MainWidget", Meta = (AllowPrivateAccess = "true"))
	UMainWidget* mMainWidget;

	FTimeline mTimeline;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* mZoomCurve;

	float mMoveForwardSpeed;
	float mMoveBackSpeed;
	float mMoveSideSpeed;

	std::bitset< static_cast<UINT>(EPlayerState::End)> mState;
	std::bitset< static_cast<UINT>(EMoveDir::End)> mMoveDir;

};
