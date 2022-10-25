// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UGameplayWidget::NativeConstruct()
{
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UGameplayWidget::PlayButtonClicked);
	}

	ScoreLabel->SetVisibility(ESlateVisibility::Hidden);
}

void UGameplayWidget::PlayButtonClicked()
{
	PlayButton->SetVisibility(ESlateVisibility::Hidden);
	ScoreLabel->SetVisibility(ESlateVisibility::Visible);

	OnPlayButtonPressed.Broadcast();
}

void UGameplayWidget::SetScoreLabel(int Score)
{
	FText CachedText = FText::FromString(TEXT("Score: ") + FString::FromInt(Score));
	ScoreLabel->SetText(CachedText);
}

void UGameplayWidget::SetTitleLabelVisibility(bool IsVisible)
{

}