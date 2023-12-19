// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

void UMainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCrosshairWidget = Cast<UCrossHairWidget>(GetWidgetFromName(TEXT("UI_Crosshair")));
}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}