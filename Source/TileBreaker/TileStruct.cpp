// Fill out your copyright notice in the Description page of Project Settings.


#include "TileStruct.h"
#include "PaperSpriteComponent.h"

UPaperSprite* FTileStruct::GetCompleteBlock() const
{
	return CompleteBlock;
}

UPaperSprite* FTileStruct::GetWoundedBlock() const
{
	return WoundedBlock;
}
