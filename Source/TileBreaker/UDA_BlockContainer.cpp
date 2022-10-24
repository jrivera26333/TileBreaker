// Fill out your copyright notice in the Description page of Project Settings.


#include "UDA_BlockContainer.h"

FTileStruct UUDA_BlockContainer::GetRandomBlock() const
{
	return BlockCombinations[FMath::RandRange(0, BlockCombinations.Num())];
}

