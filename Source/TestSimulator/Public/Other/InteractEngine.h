// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "Interface/Interactive.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractEngine.generated.h"

UCLASS()
class TESTSIMULATOR_API AInteractEngine : public AActor,public IInteractive
{
    GENERATED_BODY()

  public:
    AInteractEngine();

  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;
    virtual void Interact(class ABasePlayer* Player) override;
    virtual void ShowInteractWidget() override;

  protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UBoxComponent> CollisionBox;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class USphereComponent> TriggerSphere;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class AInteractObject> ElectricPanel;

    UPROPERTY(EditAnywhere)
    FString InteractText;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class USoundCue> EngineSound;

    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  private:
    void FixEngine(ABasePlayer* Player);
    void TurnOnEngine(ABasePlayer* Player);
    void RotateComponent(float DeltaTime);

    bool bIsFixed = false;
    bool bIsTurnOn = false;

    TObjectPtr<UStaticMeshComponent> Detail;

    TWeakObjectPtr<class USimulatorGameInstance> GameInstance;
};
