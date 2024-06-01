// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StartContextWidget.h"
#include "Components/Button.h"
#include "SimulatorGameModeBase.h"

void UStartContextWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this,&UStartContextWidget::OnClicked);
    }
}

void UStartContextWidget::OnClicked()
{
    const auto GameMode = GetWorld()->GetAuthGameMode<ASimulatorGameModeBase>();

    if (GameMode)
    {
        GameMode->SetGameState(EGameState::InProgress);
    }
}
