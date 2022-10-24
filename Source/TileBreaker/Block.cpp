// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "UDA_BlockContainer.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotaterSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Rotater"));
	RootComponent = RotaterSceneComponent;

	BlockMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Block"));
	BlockMesh->SetMobility(EComponentMobility::Movable);
	BlockMesh->SetupAttachment(RotaterSceneComponent);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	CurrentBlock = BallDataCollection->GetRandomBlock();

	if (CurrentBlock.GetCompleteBlock())
	{
		BlockMesh->SetSprite(CurrentBlock.GetCompleteBlock());
		UE_LOG(LogTemp, Warning, TEXT("Assigned Block!"));
	}
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::OnHit()
{
	if(!IsWounded)
		BlockMesh->SetSprite(CurrentBlock.GetWoundedBlock());
	else
		Destroy();
}
