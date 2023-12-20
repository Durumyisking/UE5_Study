// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"



void UCrossHairWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	mCrossHairL = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_L")));
	mCrossHairR = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_R")));
	mCrossHairU = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_U")));
	mCrossHairD = Cast<UImage>(GetWidgetFromName(TEXT("crosshair_D")));
	float inintalOffset = 150.f;
	mCrossHairU->SetRenderTranslation({ 0.f	 , inintalOffset });
	mCrossHairD->SetRenderTranslation({ 0.f	 , -inintalOffset });
	mCrossHairL->SetRenderTranslation({ inintalOffset  , 0.f });
	mCrossHairR->SetRenderTranslation({ -inintalOffset , 0.f });
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

void UCrossHairWidget::ZoomInOut(float value)
{
	float offset = 75.f + (75.f * value);
	mCrossHairU->SetRenderTranslation( { 0.f					, offset });
	mCrossHairD->SetRenderTranslation( { 0.f					, -offset });
	mCrossHairL->SetRenderTranslation( { offset	, 0.f });
	mCrossHairR->SetRenderTranslation( {-offset	, 0.f});
}

