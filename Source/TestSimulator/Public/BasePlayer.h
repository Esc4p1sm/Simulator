// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "UObject/ScriptInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer.generated.h"

UCLASS()
class TESTSIMULATOR_API ABasePlayer : public ACharacter
{
    GENERATED_BODY()

  public:
    ABasePlayer();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void PickupQuestObject(AActor* Object);
    void OnGameEnd();

    TObjectPtr<AActor> GetQuestObject() const
    {
        return QuestObject;
    }

    void SetQuestObject(AActor* Obj)
    {
        QuestObject = Obj;
    }

    void PPEPuton(bool bIsTake)
    {
        bIsTakePPE = bIsTake;
    }

  protected:
    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UCameraComponent> CameraComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<class UPhysicsHandleComponent> PhysicsHandleComponent;

    UPROPERTY(EditDefaultsOnly)
    TObjectPtr<USceneComponent> ObjectSocket;

    UPROPERTY(EditAnywhere)
    float TraceLenght = 300.f;

    UPROPERTY()
    TScriptInterface<class IInteractive> InterfaceObject;

  private:
    FHitResult LineHitResult;

    TObjectPtr<AActor> QuestObject;

    TWeakObjectPtr<class ASimulatorHUD> GameHUD;

    bool bIsTakePPE = false;

    void Interact();
    void DrawLineOfSight();
    void OnMoveForward(float Value);
    void OnMoveRight(float Value);
    void OnTakePhysicalObject();
    void OnThrowPhysicalObject();
};
