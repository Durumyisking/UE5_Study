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


	// FObjectFinder, ClassFinder는 생성자에서만 사용이 가능하다.
	// ClassFinder로 하면 아직 Class로 Instance를 생성 안한거 (이따 써서 인스턴스 만들라고 이야기 해놓는거)												클래스는_C 붙여야해!
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContents/Animation/Player/BPGhostAnim.BPGhostAnim_C'"));
	// 모든 Ghost들이 이 에셋을 공유해서 사용하도록 static 붙임

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

}
 