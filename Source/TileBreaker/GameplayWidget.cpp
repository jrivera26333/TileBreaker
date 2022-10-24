// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayWidget.h"
#include "Components/TextBlock.h"

void UGameplayWidget::SetScoreLabel(int Score)
{
	FText CachedText = FText::FromString(TEXT("Score: ") + FString::FromInt(Score));
	ScoreLabel->SetText(CachedText);
}
