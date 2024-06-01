// Fill out your copyright notice in the Description page of Project Settings.

#include "SimulatorGameInstance.h"
#include "Other/QuestManager.h"

void USimulatorGameInstance::Init()
{
    Super::Init();
}

void USimulatorGameInstance::OnStart()
{
    Super::OnStart();

    QuestManager = NewObject<UQuestManager>(GetWorld(), QuestManagerClass.Get());

    OnConfirmMistake.AddUObject(QuestManager, &UQuestManager::OnConfirmMistake);
}
