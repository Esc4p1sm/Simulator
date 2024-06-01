// Fill out your copyright notice in the Description page of Project Settings.


#include "Other/StepladderTrigger.h"
#include "Components/BoxComponent.h"
#include "Other/InteractStepladder.h"
#include "SimulatorGameInstance.h"

AStepladderTrigger::AStepladderTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
    BoxCollision                  = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

    SetRootComponent(BoxCollision);
}

void AStepladderTrigger::BeginPlay()
{
	Super::BeginPlay();

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AStepladderTrigger::OnComponentBeginOverlap);

    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    GameInstance->OnGameEnd.AddUObject(this, &AStepladderTrigger::OnGameEnd);
}

void AStepladderTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStepladderTrigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
    if (OtherActor->IsA<AInteractStepladder>())
    {
        const auto Stepladder = StaticCast<AInteractStepladder*>(OtherActor);

        if (Stepladder->GetObjectData().ObjectType == EObjectType::PhysicsType)
        {
            bIsInPlace = true;
        }
    }
}

void AStepladderTrigger::OnGameEnd()
{
    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    if (!bIsInPlace)
    {
        GameInstance->OnConfirmMistake.Broadcast(EMistakeType::StepladderLost);
    }
}
