// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "UI/MainWidget.h"
#include "Player\Ghost.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<UMainWidget> MainWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/MyContents/UI/UI_Main.UI_Main_C'"));
	if (MainWidgetClass.Succeeded())
	{
		mMainWidgetClass = MainWidgetClass.Class;
	}

	DefaultPawnClass = AGhost::StaticClass();
}

void AMyGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mMainWidgetClass))
	{
		mMainWidget = CreateWidget<UMainWidget>(GetWorld(), mMainWidgetClass);

		if (IsValid(mMainWidget))
		{
			mMainWidget->AddToViewport();
		}
	}

}

void AMyGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
