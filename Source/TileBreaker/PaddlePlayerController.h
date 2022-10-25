// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaddlePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerControllerInit);

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

public:
	FOnPlayerControllerInit OnPlayerControllerInit;
};