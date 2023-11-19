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
	// 뷰포트에 메시지 출력하는 함수
	GEngine->AddOnScreenDebugMessage(-1, duration, color, strText);
}
