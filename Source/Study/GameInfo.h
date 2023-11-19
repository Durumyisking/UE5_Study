// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

#include <bitset>

//#define UPROPERTY_EDITANY_BPRW_APC_TRUE	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

DECLARE_LOG_CATEGORY_EXTERN(MYLOG, Log, All);
							//함수포인터 이름							// 코드 라인
#define LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))

			// 여기의 인자를															//문자열로 만들어버린다
#define LOG(Format, ...) UE_LOG(MYLOG, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float duration, const FColor& color, const FString& strText);


/**
 * 
 */
class STUDY_API GameInfo
{
public:
	GameInfo();
	~GameInfo();
};
