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
	mCrossHairU->SetOpacity(0.5f);
	mCrossHairD->SetOpacity(0.5f);
	mCrossHairL->SetOpacity(0.5f);
	mCrossHairR->SetOpacity(0.5f);
}

void UCrossHairWidget::ZoomOut()
{
	mCrossHairU->SetOpacity(1.f);
	mCrossHairD->SetOpacity(1.f);
	mCrossHairL->SetOpacity(1.f);
	mCrossHairR->SetOpacity(1.f);
}
