// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/InteractObject.h"
#include "Components/BoxComponent.h"
#include "BasePlayer.h"
#include "Other/QuestObject.h"
#include "SimulatorGameInstance.h"
#include "Other/QuestManager.h"
#include "Other/InteractDoor.h"

AInteractObject::AInteractObject()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionBox                  = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    MeshComponent                 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

    SetRootComponent(CollisionBox);
    MeshComponent->SetupAttachment(GetRootComponent());
}

void AInteractObject::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();
}

void AInteractObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractObject::Interact(ABasePlayer* Player)
{
    if (!Player)
    {
        return;
    }

    if (InteractObjectData.ObjectStage == EQuestStage::None)
    {
        return;
    }

    if (this->bIsNeedQuestItem)
    {
        const auto QuestObject = StaticCast<AQuestObject*>(Player->GetQuestObject());

        if (!QuestObject)
        {
            return;
        }

        const bool IsSameStage = InteractObjectData.ObjectStage == QuestObject->GetQuestObjectData().ObjectStage;

        if (IsSameStage)
        {
            //GameInstance->OnQuestComplite.Broadcast(this->InteractObjectData.ObjectStage);

            GameInstance->GetQuestManager().Get()->MarkQuestDone(InteractObjectData.ObjectStage);

            if (InteractDoor)
            {
                StaticCast<AInteractDoor*>(InteractDoor.Get())->SetIsOpen(true);
            }

            Player->GetQuestObject()->DetachFromActor(FDetachmentTransformRules{EDetachmentRule::KeepWorld,false});
            Player->GetQuestObject().Get()->SetActorHiddenInGame(true);
            Player->SetQuestObject(nullptr);
        }
    }
    else
    {
        GameInstance->GetQuestManager().Get()->MarkQuestDone(InteractObjectData.ObjectStage);

        //GameInstance->OnQuestComplite.Broadcast(this->InteractObjectData.ObjectStage);
    }
}

void AInteractObject::ShowInteractWidget()
{
    GameInstance->OnShowInteractWidget.Broadcast(InteractObjectData.InteractText);
}
