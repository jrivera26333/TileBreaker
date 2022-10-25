// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);

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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TitleLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayButtonClicked();

public:
	void SetScoreLabel(int TargetScore);

	void SetTitleLabelVisibility(bool IsVisible);

	FOnButtonPressed OnPlayButtonPressed;
};
