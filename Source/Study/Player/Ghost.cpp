// Fill out your copyright notice in the Description page of Project Settings.


#include "Ghost.h"

AGhost::AGhost()
{
	// FObjectFinder, ClassFinder는 생성자에서만 사용이 가능하다.
	// ClassFinder로 하면 아직 Class로 Instance를 생성 안한거 (이따 써서 인스턴스 만들라고 이야기 해놓는거)												클래스는_C 붙여야해!
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/MyContents/Animation/Player/BPGhostAnim.BPGhostAnim_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimAsset.Class);
	}
}
 