// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameHUDWidget.h"
#include "Widgets/InteractWidget.h"
#include "Widgets/QuestTextWidget.h"

void UGameHUDWidget::SetInteractWidgetVisibility(FString Text, bool bIsShow)
{
    if (!InteractWidget)
    {
        return;
    }

    if (Text.IsEmpty())
    {
        return;
    }

    if (bIsShow)
    {
        InteractWidget->SetVisibility(ESlateVisibility::Visible);

        InteractWidget->SetInteractText(Text);
    }
    else
    {
        InteractWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UGameHUDWidget::SetTextQuestTextWidget(FString& Text)
{
    QuestTextWidget->SetQuestText(Text);
}
