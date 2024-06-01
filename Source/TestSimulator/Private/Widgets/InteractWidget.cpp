// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InteractWidget.h"
#include "Components/TextBlock.h"

void UInteractWidget::SetInteractText(FString& Text)
{
    if (InteractText)
    {
        InteractText->SetText(FText::FromString(Text));
    }
}
