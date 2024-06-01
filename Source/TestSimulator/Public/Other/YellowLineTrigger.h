// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YellowLineTrigger.generated.h"

UCLASS()
class TESTSIMULATOR_API AYellowLineTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	AYellowLineTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UBoxComponent> BoxCollision;

    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
