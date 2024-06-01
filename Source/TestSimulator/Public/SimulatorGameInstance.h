// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimulatorGameInstance.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API USimulatorGameInstance : public UGameInstance
{
    GENERATED_BODY()

  public:
    virtual void Init() override;
    virtual void OnStart() override;

    //FOnQuestCompliteSignature OnQuestComplite;

    FOnConfirmMistakeSignature OnConfirmMistake;

    FOnShowInteractWidgetSignature OnShowInteractWidget;

    FOnGameEndSignature OnGameEnd;

    TObjectPtr<class UQuestManager> GetQuestManager() const
    {
        return QuestManager;
    }

  protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UQuestManager> QuestManagerClass;

  private:
    TObjectPtr<UQuestManager> QuestManager;
};
