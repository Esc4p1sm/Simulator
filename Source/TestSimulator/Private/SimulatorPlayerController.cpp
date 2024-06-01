// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorPlayerController.h"
#include "SimulatorGameModeBase.h"

void ASimulatorPlayerController::BeginPlay()
{
    Super::BeginPlay();

    const auto GameMode = GetWorld()->GetAuthGameMode<ASimulatorGameModeBase>();

    if (GameMode)
    {
        GameMode->OnGameStateChange.AddUObject(this, &ASimulatorPlayerController::OnGameStateChanged);
    }
}

void ASimulatorPlayerController::OnGameStateChanged(EGameState State)
{
    if (State == EGameState::InProgress)
    {
        bShowMouseCursor = false;
        this->SetInputMode(FInputModeGameOnly());
    }
    else
    {
        bShowMouseCursor = true;
        this->SetInputMode(FInputModeUIOnly());
    }
}

void ASimulatorPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent)
    {
        InputComponent->BindAction("Pause", IE_Pressed, this, &ASimulatorPlayerController::OnPauseGame);
    }
}

void ASimulatorPlayerController::OnPauseGame()
{
    if (!GetWorld())
    {
        return;
    }

    if (!bIsGamePause)
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);

        InputComponent->GetActionBinding(0).bExecuteWhenPaused = true;
        bIsGamePause                                           = true;
    }
    else
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
        bIsGamePause = false;
    }
}
