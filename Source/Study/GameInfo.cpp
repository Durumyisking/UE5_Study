// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInfo.h"

DEFINE_LOG_CATEGORY(MYLOG)

GameInfo::GameInfo()
{
}

GameInfo::~GameInfo()
{
}

void PrintViewport(float duration, const FColor& color, const FString& strText)
{
	// GEngine : global engine pointer
	// ����Ʈ�� �޽��� ����ϴ� �Լ�
	GEngine->AddOnScreenDebugMessage(-1, duration, color, strText);
}
