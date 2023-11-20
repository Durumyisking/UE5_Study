// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
	: mPlayer(nullptr)
	, mAnimState(EPlayerAnimState::End)
	, mMoveDir(EMoveDir::End)
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// TryGetPawnOwner : 이 AnimInstance를 가지고 있는 메쉬의 Pawn을 얻어온다.
	// Player를 얻는다
	mPlayer = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (IsValid(mPlayer))
	{
		mPlayer->SetAnimInstance(this);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	PrintLogByState();
	PlayerAnimStateOperate();
	
}

void UPlayerAnimInstance::PrintLogByState()
{
	switch (mAnimState)
	{
	case EPlayerAnimState::Idle:
		PrintViewport(0.5f, FColor::Blue, "AnimState : Idle");
		break;
	case EPlayerAnimState::Move:
		PrintViewport(0.5f, FColor::Blue, "AnimState : Move");
		break;
	case EPlayerAnimState::Jump:
		break;
	case EPlayerAnimState::Run:
		PrintViewport(0.5f, FColor::Blue, "AnimState : Run");
		break;
	case EPlayerAnimState::Shoot:
		PrintViewport(0.5f, FColor::Blue, "AnimState : Shoot");
		break;
	case EPlayerAnimState::End:
		break;
	default:
		break;
	}
}

void UPlayerAnimInstance::PlayerAnimStateOperate()
{

	if (IsValid(mPlayer))
	{
		// 플레이어 상태에 따라서 애니메이션 바꿔주자

		if (mPlayer->GetPlayerState(EPlayerState::Idle))
		{
			mAnimState = EPlayerAnimState::Idle;
		}
		else if (mPlayer->GetPlayerState(EPlayerState::Move))
		{
			mAnimState = EPlayerAnimState::Move;
			if (mPlayer->GetMoveDir(EMoveDir::W))
			{
				mMoveDir = EMoveDir::W;
			}
			else
			{
				if (mPlayer->GetMoveDir(EMoveDir::A))
				{
					mMoveDir = EMoveDir::A;
				}
				else if (mPlayer->GetMoveDir(EMoveDir::D))
				{
					mMoveDir = EMoveDir::D;
				}

				if (mPlayer->GetMoveDir(EMoveDir::S))
				{
					mMoveDir = EMoveDir::S;
				}
			}

			if (mPlayer->GetPlayerState(EPlayerState::Run))
			{
				mAnimState = EPlayerAnimState::Run;
			}
			else if (mPlayer->GetPlayerState(EPlayerState::Shoot))
			{
				mAnimState = EPlayerAnimState::Shoot;
			}
		}
		else if (mPlayer->GetPlayerState(EPlayerState::Shoot))
		{
			mAnimState = EPlayerAnimState::Shoot;
		}
	}
}

void UPlayerAnimInstance::AnimNotify_CreateBullet()
{

}

void UPlayerAnimInstance::AnimNotify_ShootLoop()
{
	if (mPlayer->IsShooting())
	{

	}
}

void UPlayerAnimInstance::PlayMontage(UAnimMontage* montage)
{
	if (IsValid(montage))
	{
		if (!Montage_IsPlaying(montage))
		{
			Montage_Play(montage);
		}
	}

}
