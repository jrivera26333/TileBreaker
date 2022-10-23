// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UDA_BlockContainer.generated.h"


USTRUCT(BlueprintType)
struct FBlockSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperSprite* CompleteBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperSprite* WoundedBlock;
};


UCLASS(BlueprintType)
class TILEBREAKER_API UUDA_BlockContainer : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBlockSet> BlockCombinations;

	FBlockSet GetRandomBlock() const;
};
