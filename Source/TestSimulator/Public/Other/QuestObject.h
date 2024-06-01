// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "Interface/Interactive.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestObject.generated.h"

UCLASS()
class TESTSIMULATOR_API AQuestObject : public AActor, public IInteractive
{
    GENERATED_BODY()

  public:
    AQuestObject();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(class ABasePlayer* Player) override;
    virtual void ShowInteractWidget() override;

    const FObjectData& GetQuestObjectData() const
    {
        return QuestObjectData;
    }

  protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(EditAnywhere)
    FObjectData QuestObjectData;

  private:
    TWeakObjectPtr<class USimulatorGameInstance> GameInstance;
};
