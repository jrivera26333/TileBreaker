// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddlePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TILEBREAKER_API APaddlePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayWidget> GameplayUIWidgetClass;

	UGameplayWidget* GameplayUIWidget;
	int Score = 0;

public:
	UFUNCTION()
	void UpdateScore();

	void ResetScore();
	void SubscribeToBlockDestroyed();
};
