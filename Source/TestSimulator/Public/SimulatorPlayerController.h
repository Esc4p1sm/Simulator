// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SimulatorPlayerController.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API ASimulatorPlayerController : public APlayerController
{
    GENERATED_BODY()

  public:
    virtual void BeginPlay() override;
    void OnGameStateChanged(EGameState State);
    virtual void SetupInputComponent() override;
    void OnPauseGame();

    void SetGameIsPause(const bool State)
    {
        bIsGamePause = State;
    }

    private:
    bool bIsGamePause = false;
};
