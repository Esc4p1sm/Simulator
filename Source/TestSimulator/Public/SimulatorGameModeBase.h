// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimulatorGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API ASimulatorGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

  public:
    ASimulatorGameModeBase();

    virtual void BeginPlay() override;
    virtual void StartPlay() override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

    FOnGameStateChangeSignature OnGameStateChange;

    void SetGameState(EGameState State);

  protected:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class USoundCue> BackGroundMusic;

    EGameState GameState = EGameState::InProgress;
};
