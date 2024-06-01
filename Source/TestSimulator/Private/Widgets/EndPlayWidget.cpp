// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/EndPlayWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SimulatorPlayerController.h"
#include "SimulatorGameInstance.h"
#include "Other/QuestManager.h"

void UEndPlayWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    ExitButton->OnClicked.AddDynamic(this, &UEndPlayWidget::OnClicked);

}

void UEndPlayWidget::NativeConstruct()
{
    Super::NativeConstruct();

    CheckMistakes();
}

void UEndPlayWidget::CheckMistakes(/*uint8 Mistakes*/)
{
    const auto GameInstance = GetWorld()->GetGameInstanceChecked<USimulatorGameInstance>();

    if (!GameInstance)
    {
        return;
    }

    uint8 Mistakes = GameInstance->GetQuestManager()->GetMistakes();

    if (Mistakes & EMistakeType::YellowLine)
    {
        YellowLineViolation->SetIsChecked(true);
    }

    if (Mistakes & EMistakeType::ElectricityLost)
    {
        ElectricityViolation->SetIsChecked(true);
    }

    if (Mistakes & EMistakeType::StepladderLost)
    {
        StepladderViolation->SetIsChecked(true);
    }

    if (Mistakes & EMistakeType::PPELost)
    {
        PPEViolation->SetIsChecked(true);
    } 
}

void UEndPlayWidget::OnClicked()
{
    const auto PlayerController = GetWorld()->GetFirstPlayerController<ASimulatorPlayerController>();

    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
    }
}
