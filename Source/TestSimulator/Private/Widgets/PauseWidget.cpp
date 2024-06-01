// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/PauseWidget.h"
#include "Components/Button.h"
#include "SimulatorPlayerController.h"
#include "SimulatorGameModeBase.h"
#include "Kismet/KismetSystemLibrary.h"

bool UPauseWidget::Initialize()
{
    const bool bIsInitStatus = Super::Initialize();

    if (bIsInitStatus)
    {
        ResumeGameButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeGame);

        QuitGameButton->OnClicked.AddDynamic(this, &UPauseWidget::OnQuitGame);

        this->SetIsFocusable(true);
    }

    return bIsInitStatus;
}

void UPauseWidget::OnResumeGame()
{
    if (!GetWorld())
    {
        return;
    }

    const auto PlayerController = GetWorld()->GetFirstPlayerController<ASimulatorPlayerController>();

    if (PlayerController)
    {
        PlayerController->SetGameIsPause(false);
    }

    GetWorld()->GetAuthGameMode()->ClearPause();
}

void UPauseWidget::OnQuitGame()
{
    const auto PlayerController = GetWorld()->GetFirstPlayerController<ASimulatorPlayerController>();

    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
    }
}
