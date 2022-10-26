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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TitleLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* PlayButton;

	virtual void NativeConstruct() override;

public:
	void SetScoreLabel(int TargetScore);

	void SetTitleLabelVisibility(bool IsVisible);
};
