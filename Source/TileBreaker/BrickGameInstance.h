// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BrickGameInstance.generated.h"

UCLASS()
class TILEBREAKER_API UBrickGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};