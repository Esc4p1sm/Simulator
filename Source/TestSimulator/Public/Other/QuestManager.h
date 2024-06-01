// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestManager.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class TESTSIMULATOR_API UQuestManager : public UObject
{
    GENERATED_BODY()

  public:
    void MarkQuestDone(EQuestStage Stage);
    virtual void PostInitProperties() override;

    const FQuestData& GetCurrentQuest() const
    {
        return CurrentQuest;
    }

    const uint8& GetMistakes() const
    {
        return Mistakes;
    }

    void OnConfirmMistake(EMistakeType Type);

  protected:
    UPROPERTY(EditDefaultsOnly)
    TArray<FQuestData> QuestsData;

  private:
    FQuestData CurrentQuest;
    uint8 Mistakes = 0;
    TWeakObjectPtr<class USimulatorGameInstance> GameInstance;

    void SetQuestText();
};
