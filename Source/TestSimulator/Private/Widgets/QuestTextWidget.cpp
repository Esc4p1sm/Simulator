// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/QuestTextWidget.h"
#include "Components/TextBlock.h"

void UQuestTextWidget::SetQuestText(FString& Text)
{
    if (QuestTextBox)
    {
        QuestTextBox->SetText(FText::FromString(Text));
    }
}
