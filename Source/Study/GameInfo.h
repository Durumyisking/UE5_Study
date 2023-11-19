// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

#include <bitset>

//#define UPROPERTY_EDITANY_BPRW_APC_TRUE	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

DECLARE_LOG_CATEGORY_EXTERN(MYLOG, Log, All);
							//�Լ������� �̸�							// �ڵ� ����
#define LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))

			// ������ ���ڸ�															//���ڿ��� ����������
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
