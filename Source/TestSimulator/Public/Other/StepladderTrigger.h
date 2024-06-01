// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StepladderTrigger.generated.h"

UCLASS()
class TESTSIMULATOR_API AStepladderTrigger : public AActor
{
    GENERATED_BODY()

  public:
    AStepladderTrigger();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void OnGameEnd();

  protected:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UBoxComponent> BoxCollision;

    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  private:
    bool bIsInPlace = false;
};
