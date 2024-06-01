// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"


UINTERFACE(MinimalAPI)
class UInteractive : public UInterface
{
    GENERATED_BODY()
};


/**
 *
 */
class TESTSIMULATOR_API IInteractive
{
    GENERATED_BODY()

  public:
    virtual void Interact(class ABasePlayer* Player) PURE_VIRTUAL(IInteractive::Interact, );
    virtual void ShowInteractWidget() PURE_VIRTUAL(IInteractive::ShowInteractWidget, );
};
