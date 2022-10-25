// Fill out your copyright notice in the Description page of Project Settings.


#include "TileStruct.h"
#include "PaperSpriteComponent.h"
#include "Materials/Material.h"

UMaterialInstance* FTileStruct::GetCompleteMaterial() const
{
	return GlowCompleteMaterial;
}

UMaterialInstance* FTileStruct::GetWoundedMaterial() const
{
	return GlowWoundedMaterial;
}
