// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "Interface/Interactive.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractDoor.generated.h"

UCLASS()
class TESTSIMULATOR_API AInteractDoor : public AActor, public IInteractive
{
    GENERATED_BODY()

  public:
    AInteractDoor();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(class ABasePlayer* Player) override;
    virtual void ShowInteractWidget() override;

    void SetIsOpen(bool bIsOpen);

    //void OnQuestComplited(EQuestStage Stage);

  protected:
    UPROPERTY()
    TObjectPtr<class UTimelineComponent> TimelineComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact Door")
    TObjectPtr<USceneComponent> DoorPivot;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interact Door")
    TObjectPtr<UStaticMeshComponent> DoorMesh;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UCurveFloat> CurveFloat;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(EditAnywhere)
    FObjectData InteractObjectData;

    float AngleMax    = 90.f;
    float AngleMin    = 0.f;

    bool bIsOpened    = false;

    UPROPERTY(EditAnywhere)
    bool bCanBeOpened = false;

    UFUNCTION()
    void UpdateTimeline(float Alpha);

    private:
    TWeakObjectPtr<class USimulatorGameInstance> GameInstance;
};
