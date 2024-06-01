// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API UGameHUDWidget : public UUserWidget
{
    GENERATED_BODY()


  public:
    void SetInteractWidgetVisibility(FString Text, bool bIsShow);
    void SetTextQuestTextWidget(FString& Text);

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UInteractWidget> InteractWidget;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UQuestTextWidget> QuestTextWidget;
};
