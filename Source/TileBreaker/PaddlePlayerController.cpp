// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePlayerController.h"
#include "GameplayWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Block.h"

void APaddlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	GameplayUIWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayUIWidgetClass);
	GameplayUIWidget->AddToViewport();
	ResetScore();
	SubscribeToBlockDestroyed();
}

void APaddlePlayerController::UpdateScore()
{
	GameplayUIWidget->SetScoreLabel(++Score);
	UE_LOG(LogTemp, Warning, TEXT("Updated!"));
}

void APaddlePlayerController::ResetScore()
{
	GameplayUIWidget->SetScoreLabel(0);
}

void APaddlePlayerController::SubscribeToBlockDestroyed()
{
	TArray<AActor*> FoundBlocks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), FoundBlocks);

	for (int i = 0; i < FoundBlocks.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Subscribed!"));
		auto TempBlock = Cast<ABlock>(FoundBlocks[i]);
		TempBlock->OnBrickDeath.AddDynamic(this, &APaddlePlayerController::UpdateScore);
	}
}
