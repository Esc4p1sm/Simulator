// Fill out your copyright notice in the Description page of Project Settings.

#include "Other/InteractDoor.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "SimulatorGameInstance.h"

AInteractDoor::AInteractDoor()
{
    PrimaryActorTick.bCanEverTick         = false;
    USceneComponent* DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

    SetRootComponent(DefaultRootComponent);

    TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
    DoorPivot         = CreateDefaultSubobject<USceneComponent>(TEXT("Door Pivot"));
    CollisionBox      = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));

    DoorPivot->SetupAttachment(GetRootComponent());

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    DoorMesh->SetupAttachment(DoorPivot);

    CollisionBox->SetupAttachment(DoorMesh);
}

void AInteractDoor::BeginPlay()
{
    Super::BeginPlay();

    GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    //GameInstance->OnQuestComplite.AddUObject(this, &AInteractDoor::OnQuestComplited);

    if (CurveFloat)
    {
        FOnTimelineFloat FunctionFloatDelegate;

        FunctionFloatDelegate.BindDynamic(this, &AInteractDoor::UpdateTimeline);

        TimelineComponent->AddInterpFloat(CurveFloat, FunctionFloatDelegate);
    }
}

void AInteractDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AInteractDoor::Interact(ABasePlayer* Player)
{
    if (!bCanBeOpened || !Player)
    {
        return;
    }

    if (!bIsOpened)
    {
        bIsOpened = true;

        CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        TimelineComponent->Play();

        FTimerDelegate TimerDelegate;
        FTimerHandle TimerHandle;

        TimerDelegate.BindLambda([&]() {
            TimelineComponent->Reverse();

            CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

            bIsOpened = false;
        });

        GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 10.f, false);
    }
}

void AInteractDoor::ShowInteractWidget()
{
    GameInstance->OnShowInteractWidget.Broadcast(InteractObjectData.InteractText);
}

void AInteractDoor::UpdateTimeline(float Alpha)
{
    float Angle = FMath::Lerp(AngleMin, AngleMax, FMath::Clamp(Alpha, 0.f, 1.f));

    DoorPivot->SetRelativeRotation(FRotator{0.f, Angle, 0.f});
}

void AInteractDoor::SetIsOpen(bool bIsOpen)
{
    this->bCanBeOpened = bIsOpen;
}
//void AInteractDoor::OnQuestComplited(EQuestStage Stage)
//{
//    if (Stage == EQuestStage::CardStage)
//    {
//        this->bCanBeOpened = true;
//    }
//}
