// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/QuestObject.h"
#include "Components/SphereComponent.h"
#include "BasePlayer.h"
#include "SimulatorGameInstance.h"

AQuestObject::AQuestObject()
{
	PrimaryActorTick.bCanEverTick = true;
    CollisionSphere               = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
    MeshComponent                 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

    SetRootComponent(CollisionSphere);
    MeshComponent->SetupAttachment(GetRootComponent());
}

void AQuestObject::BeginPlay()
{
	Super::BeginPlay();

    GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();
}

void AQuestObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestObject::Interact(ABasePlayer* Player)
{
    if (!Player)
    {
        return;
    }

    if (QuestObjectData.ObjectType == EObjectType::PPE)
    {
        Player->PPEPuton(true);

        this->Destroy();

        return;
    }
    else
    {
        CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Player->PickupQuestObject(this);
    }  
}

void AQuestObject::ShowInteractWidget()
{
    GameInstance->OnShowInteractWidget.Broadcast(QuestObjectData.InteractText);
}

