// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/InteractEngine.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "BasePlayer.h"
#include "SimulatorGameInstance.h"
#include "Other/QuestManager.h"
#include "Other/InteractObject.h"
#include "SimulatorGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AInteractEngine::AInteractEngine()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionBox                  = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    TriggerSphere                 = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
    MeshComponent                 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

    SetRootComponent(CollisionBox);

    MeshComponent->SetupAttachment(GetRootComponent());

    TriggerSphere->SetupAttachment(GetRootComponent());
}

void AInteractEngine::BeginPlay()
{
    Super::BeginPlay();

    TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractEngine::OnComponentBeginOverlap);

    GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    auto Components = this->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Detail"));

    Detail = StaticCast<UStaticMeshComponent*>(Components[0]);
}

void AInteractEngine::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (this->bIsTurnOn)
    {
        RotateComponent(DeltaTime);
    }
}

void AInteractEngine::Interact(ABasePlayer* Player)
{
    if (!Player)
    {
        return;
    }

    if (!bIsFixed)
    {
        const bool bIsCurrentQuestStage = GameInstance->GetQuestManager()->GetCurrentQuest().QuestStage == EQuestStage::FixEngine;

        if (!bIsCurrentQuestStage)
        {
            GameInstance->OnConfirmMistake.Broadcast(EMistakeType::ElectricityLost);

            return;
        }

        FixEngine(Player);
    }
    else
    {
        TurnOnEngine(Player);
    }
}

void AInteractEngine::ShowInteractWidget()
{
    GameInstance->OnShowInteractWidget.Broadcast(InteractText);
}

void AInteractEngine::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA<ABasePlayer>())
    {
        //GameInstance->OnQuestComplite.Broadcast(EQuestStage::BrokenEngine);
        GameInstance->GetQuestManager()->MarkQuestDone(EQuestStage::BrokenEngine);

        TriggerSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void AInteractEngine::FixEngine(ABasePlayer* Player)
{
    if (Player->GetQuestObject()->Tags[0] != FName("Tools") || !Player->GetQuestObject())
    {
        return;
    }

    if (Player->GetQuestObject()->Tags[0] == FName("Tools"))
    {
        //GameInstance->OnQuestComplite.Broadcast(EQuestStage::FixEngine);
        GameInstance->GetQuestManager()->MarkQuestDone(EQuestStage::FixEngine);

        Player->GetQuestObject()->DetachFromActor(FDetachmentTransformRules{EDetachmentRule::KeepWorld, false});
        Player->GetQuestObject().Get()->SetActorHiddenInGame(true);

        ElectricPanel->SetObjectData(EQuestStage::ElectricityOn);

        bIsFixed = true;
    }
}

void AInteractEngine::TurnOnEngine(ABasePlayer* Player)
{
    const bool bIsFinalQuest = GameInstance->GetQuestManager().Get()->GetCurrentQuest().QuestStage == EQuestStage::StartEngine;

    if (bIsFinalQuest)
    {
        this->bIsTurnOn = true;

        if (EngineSound)
        {
            UGameplayStatics::SpawnSoundAtLocation(GetWorld(), EngineSound, GetActorLocation());
        }

        GameInstance->OnGameEnd.Broadcast();

        const auto GameMode = GetWorld()->GetAuthGameMode<ASimulatorGameModeBase>();

        if (GameMode)
        {
            GameMode->SetGameState(EGameState::EndPlay);
        }
    }
}

void AInteractEngine::RotateComponent(float DeltaTime)
{
    float AngularSpeed = 360 * DeltaTime;

    FQuat DetailRotation = FQuat{FRotator{AngularSpeed, 0, 0}};

    Detail->AddRelativeRotation(DetailRotation);
}
