// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/QuestManager.h"
#include "SimulatorPlayerController.h"
#include "SimulatorHUD.h"
#include "Kismet/GameplayStatics.h"

void UQuestManager::MarkQuestDone(EQuestStage Stage)
{
    if (QuestsData.IsEmpty())
    {
        return;
    }

    if (Stage == CurrentQuest.QuestStage)
    {
        CurrentQuest.QuestStatus = EQuestStatus::Complited;
    }

    if (CurrentQuest.QuestStatus != EQuestStatus::Complited)
    {
        return;
    }

    for (auto& Quest : QuestsData)
    {
        if (Quest.QuestStatus == EQuestStatus::Inactive)
        {
            Quest.QuestStatus = EQuestStatus::Active;

            CurrentQuest = Quest;

            break;
        }
    }

    SetQuestText();
}

void UQuestManager::PostInitProperties()
{
    Super::PostInitProperties();

    if (!QuestsData.IsEmpty())
    {
        CurrentQuest = QuestsData[0];
    }
}

void UQuestManager::OnConfirmMistake(EMistakeType Type)
{
    Mistakes |= Type;
}

void UQuestManager::SetQuestText()
{
    if (CurrentQuest.QuestStage == EQuestStage::None)
    {
        return;
    }

    const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);

    if (!PlayerController)
    {
        return;
    }

    const auto HUD = PlayerController->GetHUD<ASimulatorHUD>();

    if (!HUD)
    {
        return;
    }

    switch (CurrentQuest.QuestStage)
    {
    case EQuestStage::CardStage:
        HUD->SetQuestText(FString("Task: Take a card and open the door"));
        break;

    case EQuestStage::BrokenEngine:
        HUD->SetQuestText(FString("Task: Find the broken engine"));
        break;

    case EQuestStage::ElectricityOff:
        HUD->SetQuestText(FString("Task: Turn off the electricity"));
        break;

    case EQuestStage::FixEngine:
        HUD->SetQuestText(FString("Task: Find the tools and fix the engine"));
        break;

    case EQuestStage::ElectricityOn:
        HUD->SetQuestText(FString("Task: Turn on the electricity"));
        break;

    case EQuestStage::StartEngine:
        HUD->SetQuestText(FString("Task: Start the engine"));
        break;
    }
}
