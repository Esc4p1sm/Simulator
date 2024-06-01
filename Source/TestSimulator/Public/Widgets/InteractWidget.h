// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTSIMULATOR_API UInteractWidget : public UUserWidget
{
	GENERATED_BODY()

    public:
    void SetInteractText(FString& Text);

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> InteractText;
};
