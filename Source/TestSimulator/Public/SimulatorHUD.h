// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SimulatorHUD.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API ASimulatorHUD : public AHUD
{
    GENERATED_BODY()

  public:
    virtual void BeginPlay() override;
    void OnGameStateChange(EGameState State);
    void OnShowInteractWidget(FString& Text);
    void HideInteractWidget();
    void SetQuestText(FString Text);

  protected:
    UPROPERTY()
    TMap<EGameState, TObjectPtr<class UUserWidget>> GameWidgets;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> GameHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> InstructionWidgetClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> EndPlayWidgetClass;

    private:
    TObjectPtr<UUserWidget> CurrentWidget;
};
