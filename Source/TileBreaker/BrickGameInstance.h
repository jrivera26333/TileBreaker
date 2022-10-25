// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BrickGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TILEBREAKER_API UBrickGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

private:
	UFUNCTION()
	void SubtractLife();

	UFUNCTION()
	void UpdateScore();

	void ResetScore();
	void SubscribeToBallDestroyed();
	void SubscribeToBlockDestroyed();
	void SubscribeToPlayerControllerCreated();

	void AddLife();
	void CreateViewport();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayWidget> GameplayUIWidgetClass;

	UGameplayWidget* GameplayUIWidget;

	int Score = 0;
	int MaxAmountOfBalls = 3;
	int CurrentAmountOfBallsRemaining = 0;
};