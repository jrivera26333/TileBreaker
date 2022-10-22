// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TileBreakerGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetBall); //Subtract a life and check if its gameover

/**
 * 
 */
UCLASS()
class TILEBREAKER_API ATileBreakerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	FOnResetBall OnBallReset;

	int AmountOfBallsRemaining = 3;
	int CurrentAmountOfBallsRemaining = 0;

private:
	UFUNCTION()
	void SubtractLife();

	void AddLife();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
