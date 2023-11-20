// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

AGhost::AGhost()
{
	// FObjectFinder, ClassFinder�� �����ڿ����� ����� �����ϴ�.
	// ClassFinder�� �ϸ� ���� Class�� Instance�� ���� ���Ѱ� (�̵� �Ἥ �ν��Ͻ� ������ �̾߱� �س��°�)												Ŭ������_C �ٿ�����!
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContents/Animation/Player/BPGhostAnim.BPGhostAnim_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}
}
 