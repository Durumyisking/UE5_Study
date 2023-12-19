// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

AGhost::AGhost()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMShoot(TEXT("/Script/Engine.AnimMontage'/Game/MyContents/Animation/Montages/Ghost/AM_Ghost_Shoot.AM_Ghost_Shoot'"));
	if (AMShoot.Succeeded())
	{
		mUpperBodyMontageMap.Add("Shoot", AMShoot.Object);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AMZoomStart(TEXT("/Script/Engine.AnimMontage'/Game/MyContents/Animation/Montages/Ghost/AM_Ghost_ZoomStart.AM_Ghost_ZoomStart'"));
	if (AMZoomStart.Succeeded())
	{
		mUpperBodyMontageMap.Add("ZoomStart", AMZoomStart.Object);
	}


	// FObjectFinder, ClassFinder�� �����ڿ����� ����� �����ϴ�.
	// ClassFinder�� �ϸ� ���� Class�� Instance�� ���� ���Ѱ� (�̵� �Ἥ �ν��Ͻ� ������ �̾߱� �س��°�)												Ŭ������_C �ٿ�����!
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContents/Animation/Player/BPGhostAnim.BPGhostAnim_C'"));
	// ��� Ghost���� �� ������ �����ؼ� ����ϵ��� static ����

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

}
 