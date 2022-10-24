// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileStruct.generated.h"

USTRUCT(BlueprintType)
struct FTileStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperSprite* CompleteBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UPaperSprite* WoundedBlock;

	UPaperSprite* GetCompleteBlock() const;
	UPaperSprite* GetWoundedBlock() const;
};