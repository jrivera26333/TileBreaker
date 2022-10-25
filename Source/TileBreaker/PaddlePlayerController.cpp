// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePlayerController.h"

void APaddlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	OnPlayerControllerInit.Broadcast();
}