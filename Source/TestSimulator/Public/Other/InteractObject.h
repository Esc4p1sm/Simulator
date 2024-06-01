// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "Interface/Interactive.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractObject.generated.h"

UCLASS()
class TESTSIMULATOR_API AInteractObject : public AActor, public IInteractive
{
    GENERATED_BODY()

  public:
    AInteractObject();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(class ABasePlayer* Player) override;
    virtual void ShowInteractWidget() override;

    void SetObjectData(EQuestStage Stage)
    {
        InteractObjectData.ObjectStage = Stage;
    }

    const FObjectData& GetInteractObjectData() const
    {
        return InteractObjectData;
    }

  protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(EditAnywhere)
    FObjectData InteractObjectData;

    UPROPERTY(EditAnywhere)
    TObjectPtr<AActor> InteractDoor;

    UPROPERTY(EditAnywhere)
    bool bIsNeedQuestItem = false;

  private:
    TWeakObjectPtr<class USimulatorGameInstance> GameInstance;
};
