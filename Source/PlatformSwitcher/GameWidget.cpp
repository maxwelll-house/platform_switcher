// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformSwitcher.h"
#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("MessageBlock"));

	if (MessageText == nullptr) {
		MessageText = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}


void UGameWidget::OnGameOver(bool win)
{
	if (MessageText != nullptr) {
		if (win) {
			MessageText->SetText(FText::FromString(FString(TEXT("You won!\nPress R to play again"))));
		}
		else {
			MessageText->SetText(FText::FromString(FString(TEXT("You lost:\nPress R to play again"))));
		}
	}
}
