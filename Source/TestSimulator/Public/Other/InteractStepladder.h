// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractStepladder.generated.h"

UCLASS()
class TESTSIMULATOR_API AInteractStepladder : public AActor
{
    GENERATED_BODY()

  public:
    AInteractStepladder();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

    const FObjectData& GetObjectData() const
    {
        return InteractObjectData;
    }

  protected:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere)
    FObjectData InteractObjectData;
};
