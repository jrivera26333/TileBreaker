// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickGameInstance.h"
#include "Block.h"
#include "DeathArea.h"
#include "GameplayWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PaddlePlayerController.h"


void UBrickGameInstance::Init()
{
	Super::Init();

	SubscribeToBallDestroyed();
	SubscribeToPlayerControllerCreated();
	SubscribeToBlockDestroyed();
}

/// <summary>
/// Not Implemented yet
/// </summary>
void UBrickGameInstance::AddLife()
{
	CurrentAmountOfBallsRemaining++;
}

void UBrickGameInstance::UpdateScore()
{
	GameplayUIWidget->SetScoreLabel(++Score);
}

void UBrickGameInstance::CreateViewport()
{
	UE_LOG(LogTemp, Warning, TEXT("Subscribed Viewport!"));

	if (IsValid(GameplayUIWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Valid!"));
		GameplayUIWidget = CreateWidget<UGameplayWidget>(GetWorld(), GameplayUIWidgetClass);
		GameplayUIWidget->AddToViewport();
		ResetScore();
	}
}

void UBrickGameInstance::ResetScore()
{
	GameplayUIWidget->SetScoreLabel(0);
	CurrentAmountOfBallsRemaining = MaxAmountOfBalls;
}

void UBrickGameInstance::SubtractLife()
{
	CurrentAmountOfBallsRemaining--;
	if (CurrentAmountOfBallsRemaining <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reset!"));
	}
}

void UBrickGameInstance::SubscribeToBallDestroyed()
{
	ADeathArea* DeathArea = Cast<ADeathArea>(UGameplayStatics::GetActorOfClass(this, ADeathArea::StaticClass()));

	if (IsValid(DeathArea))
	{
		DeathArea->OnBallDeath.AddDynamic(this, &UBrickGameInstance::SubtractLife);
	}
}

void UBrickGameInstance::SubscribeToPlayerControllerCreated()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying Subscribed Player Controller!"));

	//APaddlePlayerController* PaddlePlayerController = Cast<APaddlePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	auto PaddlePlayerController = (UGameplayStatics::GetPlayerController(this, 0));

	if (IsValid(PaddlePlayerController))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller!"));
	}

	//if (IsValid(PaddlePlayerController))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Subscribed Player Controller!"));
	//	PaddlePlayerController->OnPlayerControllerInit.AddDynamic(this, &UBrickGameInstance::CreateViewport);
	//}
}

void UBrickGameInstance::SubscribeToBlockDestroyed()
{
	TArray<AActor*> FoundBlocks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABlock::StaticClass(), FoundBlocks);

	for (int i = 0; i < FoundBlocks.Num(); i++)
	{
		auto TempBlock = Cast<ABlock>(FoundBlocks[i]);
		TempBlock->OnBrickDeath.AddDynamic(this, &UBrickGameInstance::UpdateScore);
	}
}