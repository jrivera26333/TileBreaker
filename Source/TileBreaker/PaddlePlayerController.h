// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddlePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetCreated);

UCLASS()
class TILEBREAKER_API APaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SubtractLife();

	UFUNCTION()
	void UpdateScore();

	void ResetScore();
	void CreateUIWidget();
	void SubscribeToBallDestroyed();
	void SubscribeToBlockDestroyed();

	void AddLife();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UGameplayWidget> GameplayUIWidgetClass;

	UGameplayWidget* GameplayUIWidget;

	int Score = 0;
	int MaxAmountOfBalls = 3;
	int CurrentAmountOfBallsRemaining = 0;
};