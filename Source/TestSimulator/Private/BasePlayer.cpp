// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayer.h"
#include "Camera\CameraComponent.h"
#include "Interface/Interactive.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "SimulatorPlayerController.h"
#include "SimulatorHUD.h"
#include "SimulatorGameInstance.h"

ABasePlayer::ABasePlayer()
{
    PrimaryActorTick.bCanEverTick = true;
    CameraComponent               = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    PhysicsHandleComponent        = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle Component"));
    ObjectSocket                  = CreateDefaultSubobject<USceneComponent>(TEXT("Object Socket"));

    CameraComponent->SetupAttachment(GetRootComponent());
    ObjectSocket->SetupAttachment(GetRootComponent());
}

void ABasePlayer::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerController = GetWorld()->GetFirstPlayerController<ASimulatorPlayerController>();

    if (PlayerController)
    {
        GameHUD = PlayerController->GetHUD<ASimulatorHUD>();
    }

    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    GameInstance->OnGameEnd.AddUObject(this, &ABasePlayer::OnGameEnd);
}

void ABasePlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PhysicsHandleComponent->GrabbedComponent)
    {
        const FVector TargetLocation = CameraComponent->GetComponentLocation() + 200 * CameraComponent->GetForwardVector();

        PhysicsHandleComponent->SetTargetLocation(TargetLocation);
    }

    DrawLineOfSight();
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Forward", this, &ABasePlayer::OnMoveForward);
    PlayerInputComponent->BindAxis("Right", this, &ABasePlayer::OnMoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Interact", IE_Released, this, &ABasePlayer::Interact);
    PlayerInputComponent->BindAction("Take", IE_Released, this, &ABasePlayer::OnTakePhysicalObject);
    PlayerInputComponent->BindAction("Throw", IE_Released, this, &ABasePlayer::OnThrowPhysicalObject);
}

void ABasePlayer::PickupQuestObject(AActor* Object)
{
    if (!Object)
    {
        return;
    }

    if (!QuestObject)
    {
        QuestObject = Object;
    }

    if (QuestObject)
    {
        QuestObject->AttachToComponent(ObjectSocket, FAttachmentTransformRules{EAttachmentRule::KeepWorld, true});
    }
}

void ABasePlayer::Interact()
{
    if (InterfaceObject.GetInterface() && InterfaceObject)
    {
        InterfaceObject->Interact(this);
    }
}

void ABasePlayer::DrawLineOfSight()
{
    const FVector TraceStart = CameraComponent->GetComponentLocation();
    const FVector TraceEnd   = TraceStart + TraceLenght * CameraComponent->GetForwardVector();

    GetWorld()->LineTraceSingleByChannel(OUT LineHitResult, TraceStart, TraceEnd, INTERACT_TRACE_CHANNEL);

    if (LineHitResult.bBlockingHit)
    {
        const bool bHasInterface = !LineHitResult.GetActor()->Implements<UInteractive>() || LineHitResult.GetActor() == InterfaceObject.GetObject();

        if (bHasInterface)
        {
            return;
        }

        InterfaceObject = LineHitResult.GetActor();

        if (InterfaceObject)
        {
            InterfaceObject->ShowInteractWidget();
        }
    }
    else
    {
        if (GameHUD.IsValid())
        {
            GameHUD->HideInteractWidget();
        }

        InterfaceObject = nullptr;
    }
}

void ABasePlayer::OnMoveForward(float Value)
{
    if (Value != 0.0f)
    {
        this->AddMovementInput(GetActorForwardVector(), Value);
    }
}

void ABasePlayer::OnMoveRight(float Value)
{
    if (Value != 0.0f)
    {
        this->AddMovementInput(GetActorRightVector(), Value);
    }
}

void ABasePlayer::OnTakePhysicalObject()
{
    if (!LineHitResult.Component.IsValid())
    {
        return;
    }

    if (LineHitResult.Component->IsSimulatingPhysics())
    {
        const FVector ComponentLocation = LineHitResult.Component->GetComponentLocation();

        PhysicsHandleComponent->GrabComponent(LineHitResult.GetComponent(), NAME_None, ComponentLocation, true);
    }
}

void ABasePlayer::OnThrowPhysicalObject()
{
    if (PhysicsHandleComponent->GrabbedComponent)
    {
        PhysicsHandleComponent->ReleaseComponent();
    }
}

void ABasePlayer::OnGameEnd()
{
    const auto PlayerController = GetController<ASimulatorPlayerController>();

    this->DisableInput(PlayerController);

    if (!bIsTakePPE)
    {
        const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

        GameInstance->OnConfirmMistake.Broadcast(EMistakeType::PPELost);
    }
}
