// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SimulatorCoreTypes.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndPlayWidget.generated.h"

/**
 *
 */
UCLASS()
class TESTSIMULATOR_API UEndPlayWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    void CheckMistakes(/*uint8 Mistakes*/);

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UCheckBox> YellowLineViolation;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCheckBox> PPEViolation;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCheckBox> StepladderViolation;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCheckBox> ElectricityViolation;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> ExitButton;

    UFUNCTION()
    void OnClicked();
};
