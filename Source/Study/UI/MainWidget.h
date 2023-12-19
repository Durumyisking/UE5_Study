// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CrossHairWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UCrossHairWidget* GetCrosshairWidget() { return mCrosshairWidget; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crosshair", meta = (AllowPrivateAccess = "true"))
	UCrossHairWidget* mCrosshairWidget;
};
