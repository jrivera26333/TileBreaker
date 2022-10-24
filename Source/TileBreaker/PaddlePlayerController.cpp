// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePlayerController.h"
#include "GameplayWidget.h"
#include "Blueprint/UserWidget.h"

void APaddlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameplayUIWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayUIWidgetClass);
	GameplayUIWidget->AddToViewport();
	
	GameplayUIWidget->SetScoreLabel(0);
}