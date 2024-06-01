// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/InteractStepladder.h"
#include "Components/BoxComponent.h"

AInteractStepladder::AInteractStepladder()
{
	PrimaryActorTick.bCanEverTick = true;
    CollisionBox  = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));

    SetRootComponent(CollisionBox);
    MeshComponent->SetupAttachment(GetRootComponent());
}

void AInteractStepladder::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractStepladder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

