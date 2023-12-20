// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{

}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("Hello와 World!!"));

	int32 IntValue = 32;
	float FloatValue = 3.141592f;

	FString FIS = FString::Printf(TEXT("Int:%d Float:%f"), IntValue, FloatValue);
	FString FS = FString::SanitizeFloat(FloatValue);
	FString IS = FString::FromInt(IntValue);

	UE_LOG(LogTemp, Log, TEXT("%s"), *FIS);
	UE_LOG(LogTemp, Log, TEXT("%s , %s"), *FS, *IS);
}

