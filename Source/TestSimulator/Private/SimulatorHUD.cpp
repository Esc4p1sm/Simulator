// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorHUD.h"
#include "SimulatorGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "SimulatorGameInstance.h"
#include "Widgets/GameHUDWidget.h"
#include "Widgets/EndPlayWidget.h"
#include "Other/QuestManager.h"

void ASimulatorHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), GameHUDWidgetClass));
    GameWidgets.Add(EGameState::StartPlay, CreateWidget<UUserWidget>(GetWorld(), InstructionWidgetClass));
    GameWidgets.Add(EGameState::EndPlay, CreateWidget<UUserWidget>(GetWorld(), EndPlayWidgetClass));

    const auto GameMode = GetWorld()->GetAuthGameMode<ASimulatorGameModeBase>();

    if (GameMode)
    {
        GameMode->OnGameStateChange.AddUObject(this, &ASimulatorHUD::OnGameStateChange);
    }

    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    if (GameInstance)
    {
        GameInstance->OnShowInteractWidget.AddUObject(this, &ASimulatorHUD::OnShowInteractWidget);
    }
}

void ASimulatorHUD::OnGameStateChange(EGameState State)
{
    if (GameWidgets.IsEmpty())
    {
        return;
    }

    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromParent();
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (CurrentWidget)
    {
        CurrentWidget->AddToViewport();
        // CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->SetKeyboardFocus();
    }
}

void ASimulatorHUD::OnShowInteractWidget(FString& Text)
{
    if (GameWidgets[EGameState::InProgress])
    {
        StaticCast<UGameHUDWidget*>(GameWidgets[EGameState::InProgress])->SetInteractWidgetVisibility(Text, true);
    }
}

void ASimulatorHUD::HideInteractWidget()
{
    if (GameWidgets[EGameState::InProgress])
    {
        StaticCast<UGameHUDWidget*>(GameWidgets[EGameState::InProgress])->SetInteractWidgetVisibility("None", false);
    }
}

void ASimulatorHUD::SetQuestText(FString Text)
{
    if (GameWidgets[EGameState::InProgress])
    {
        StaticCast<UGameHUDWidget*>(GameWidgets[EGameState::InProgress])->SetTextQuestTextWidget(Text);
    }
}


