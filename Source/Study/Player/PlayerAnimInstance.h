// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	EPlayerAnimState GetAnimState() const { return mAnimState; }
	EMoveDir GetMoveDir() const { return mMoveDir; }
	bool IsZooming() const { return mbZooming; }
	void SetZoomOn() { mbZooming = true; }
	void SetZoomOff() { mbZooming = false; }

	//UFUNCTION(meta = (BlueprintThreadSafe))
	//UCharacterMovementComponent* GetCharacterMovementComponent() const { return mCharacterMovement; }

	void PrintLogByState();
	void PlayerAnimStateOperate();

	// notifies

	UFUNCTION()
	void AnimNotify_CreateBullet();
	UFUNCTION()
	void AnimNotify_ShootLoop();
	UFUNCTION()
	void AnimNotify_ShootEnd();
	UFUNCTION()
	void AnimNotify_ZoomEnd();


	void PlayMontage(UAnimMontage* montage);
	void StopMontage(UAnimMontage* montage, float inBlendOutTime = 0.1f);

private:
	class APlayerCharacter* mPlayer;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* mCharacterMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimState mAnimState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMoveDir mMoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8 mbZooming:1;


};

