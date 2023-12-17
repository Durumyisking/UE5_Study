// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"



void UCrossHairWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCrossHairL = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_L")));
	mCrossHairR = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_R")));
	mCrossHairU = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_U")));
	mCrossHairD = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_D")));
}

void UCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCrossHairWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCrossHairWidget::ZoomIn()
{
	
}
