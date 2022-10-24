// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TileStruct.h"
#include "UDA_BlockContainer.generated.h"

UCLASS(BlueprintType)
class TILEBREAKER_API UUDA_BlockContainer : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTileStruct> BlockCombinations;

	struct FTileStruct GetRandomBlock() const;
};