// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BrickGameInstance.h"
#include "GameplayWidget.h"
#include "DeathArea.h"
#include "Block.h"

void APaddlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	CreateUIWidget();

	SubscribeToBallDestroyed();
	SubscribeToBlockDestroyed();
}

void APaddlePlayerController::CreateUIWidget()
{	
	UE_LOG(LogTemp, Warning, TEXT("Subscribed Viewport!"));
	GameplayUIWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayUIWidgetClass);

	if (IsValid(GameplayUIWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid!"));
		GameplayUIWidget->AddToViewport();
		ResetScore();
	}
}

/// <summary>
/// Not Implemented yet
/// </summary>
void APaddlePlayerController::AddLife()
{
	CurrentAmountOfBallsRemaining++;
}

void APaddlePlayerController::UpdateScore()
{
	UE_LOG(LogTemp, Warning, TEXT("Updated Score!"));
	GameplayUIWidget->SetScoreLabel(++Score);
}

void APaddlePlayerController::ResetScore()
{
	GameplayUIWidget->SetScoreLabel(0);
	CurrentAmountOfBallsRemaining = MaxAmountOfBalls;
}

void APaddlePlayerController::SubtractLife()
{
	CurrentAmountOfBallsRemaining--;
	if (CurrentAmountOfBallsRemaining <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reset!"));
	}
}

void APaddlePlayerController::SubscribeToBallDestroyed()
{
	ADeathArea* DeathArea = Cast<ADeathArea>(UGameplayStatics::GetActorOfClass(this, ADeathArea::StaticClass()));

	if (IsValid(DeathArea))
	{
		DeathArea->OnBallDeath.AddDynamic(this, &APaddlePlayerController::SubtractLife);
	}
}

void APaddlePlayerController::SubscribeToBlockDestroyed()
{
	TArray<AActor*> FoundBlocks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), FoundBlocks);

	for (int i = 0; i < FoundBlocks.Num(); i++)
	{
		auto TempBlock = Cast<ABlock>(FoundBlocks[i]);
		TempBlock->OnBrickDeath.AddDynamic(this, &APaddlePlayerController::UpdateScore);
	}
}