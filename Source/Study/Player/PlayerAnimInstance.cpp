// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
	: mAnimState(EPlayerAnimState::End)
	, mMoveDir(EMoveDir::End)
{
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

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
	case EPlayerAnimState::End:
		break;
	default:
		break;
	}

	// TryGetPawnOwner : 이 AnimInstance를 가지고 있는 메쉬의 Pawn을 얻어온다.
	// Player를 얻는다
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		// 플레이어 상태에 따라서 애니메이션 바꿔주자

		if (player->GetPlayerState(EPlayerState::Idle))
		{
			mAnimState = EPlayerAnimState::Idle;
		}
		else if (player->GetPlayerState(EPlayerState::Move))
		{
			mAnimState = EPlayerAnimState::Move;
			if (player->GetMoveDir(EMoveDir::W))
			{
				mMoveDir = EMoveDir::W;
			}
			else
			{
				if (player->GetMoveDir(EMoveDir::A))
				{
					mMoveDir = EMoveDir::A;
				}
				else if (player->GetMoveDir(EMoveDir::D))
				{
					mMoveDir = EMoveDir::D;
				}

				if (player->GetMoveDir(EMoveDir::S))
				{
					mMoveDir = EMoveDir::S;
				}
			}

			if (player->GetPlayerState(EPlayerState::Run))
			{
				mAnimState = EPlayerAnimState::Run;
			}
		}

	}
}
