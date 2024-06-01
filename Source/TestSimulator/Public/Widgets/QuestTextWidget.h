// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTSIMULATOR_API UQuestTextWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
    void SetQuestText(FString& Text);

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UTextBlock> QuestTextBox;
};
