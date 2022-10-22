// Copyright Epic Games, Inc. All Rights Reserved.


#include "TileBreakerGameModeBase.h"
#include "DeathArea.h"
#include "Kismet/GameplayStatics.h"

void ATileBreakerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Subscribing to OnDeathEvent
	ADeathArea* DeathArea = Cast<ADeathArea>(UGameplayStatics::GetActorOfClass(this, ADeathArea::StaticClass()));

	if (IsValid(DeathArea))
	{
		DeathArea->OnBallDeath.AddDynamic(this, &ATileBreakerGameModeBase::SubtractLife);
	}

	CurrentAmountOfBallsRemaining = AmountOfBallsRemaining;
}

void ATileBreakerGameModeBase::SubtractLife()
{
	UE_LOG(LogTemp, Warning, TEXT("Life!"));

	CurrentAmountOfBallsRemaining--;
	if (CurrentAmountOfBallsRemaining <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Over!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Reset!"));
		OnBallReset.Broadcast();
	}
}

void ATileBreakerGameModeBase::AddLife()
{
	CurrentAmountOfBallsRemaining++;
}