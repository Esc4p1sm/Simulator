// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API UPauseWidget : public UUserWidget
{
    GENERATED_BODY()

    public:
    virtual bool Initialize() override;

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> ResumeGameButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> QuitGameButton;

    UFUNCTION()
    void OnResumeGame();

    UFUNCTION()
    void OnQuitGame();
};
