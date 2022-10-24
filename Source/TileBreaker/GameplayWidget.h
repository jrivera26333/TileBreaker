// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class TILEBREAKER_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()	

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreLabel;

public:
	void SetScoreLabel(int TargetScore);
};
