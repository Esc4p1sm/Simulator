// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/YellowLineTrigger.h"
#include "Components/BoxComponent.h"
#include "BasePlayer.h"
#include "SimulatorGameInstance.h"
#include "SimulatorCoreTypes.h"

AYellowLineTrigger::AYellowLineTrigger()
{
    PrimaryActorTick.bCanEverTick = true;
    BoxCollision                  = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));

    SetRootComponent(BoxCollision);
}

void AYellowLineTrigger::BeginPlay()
{
    Super::BeginPlay();

    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AYellowLineTrigger::OnComponentBeginOverlap);
}

void AYellowLineTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AYellowLineTrigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
    if (OtherActor->IsA<ABasePlayer>())
    {
        const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

        GameInstance->OnConfirmMistake.Broadcast(EMistakeType::YellowLine);
    }
}
