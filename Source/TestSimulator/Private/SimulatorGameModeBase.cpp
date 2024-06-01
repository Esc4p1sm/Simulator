// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorGameModeBase.h"
#include "BasePlayer.h"
#include "SimulatorPlayerController.h"
#include "SimulatorGameInstance.h"
#include "Other/QuestManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASimulatorGameModeBase::ASimulatorGameModeBase()
{
    DefaultPawnClass      = ABasePlayer::StaticClass();
    PlayerControllerClass = ASimulatorPlayerController::StaticClass();
}

void ASimulatorGameModeBase::BeginPlay()
{
    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    if (GameInstance)
    {
        //GameInstance->OnQuestComplite.AddUObject(GameInstance->GetQuestManager().Get(), &UQuestManager::OnMarkQuestDone);
        //GameInstance->OnConfirmMistake.AddUObject(GameInstance->GetQuestManager(), &UQuestManager::OnConfirmMistake);
    }
}

void ASimulatorGameModeBase::StartPlay()
{
    Super::StartPlay();

    if (BackGroundMusic)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), BackGroundMusic);
    }

    if (GetWorld())
    {
        this->SetGameState(EGameState::StartPlay);
    }  
}

bool ASimulatorGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const bool bIsPauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if (bIsPauseSet)
    {
        this->SetGameState(EGameState::Pause);
    }

    return bIsPauseSet;
}

bool ASimulatorGameModeBase::ClearPause()
{
    const bool bIsPauseCleared = Super::ClearPause();

    if (bIsPauseCleared)
    {
        this->SetGameState(EGameState::InProgress);
    }

    return bIsPauseCleared;
}

void ASimulatorGameModeBase::SetGameState(EGameState State)
{
    if (State == GameState)
    {
        return;
    }

    GameState = State;

    if (OnGameStateChange.IsBound())
    {
        OnGameStateChange.Broadcast(GameState);
    }
}
