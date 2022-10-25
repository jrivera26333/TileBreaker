// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "UDA_BlockContainer.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Rotater"));
	RootComponent = BoxCollision;

	BlockMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Block"));
	BlockMesh->SetMobility(EComponentMobility::Movable);
	BlockMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	CurrentBlock = BallDataCollection->GetRandomBlock();

	if (CurrentBlock.GetCompleteMaterial())
	{
		BlockMesh->SetMaterial(0, CurrentBlock.GetCompleteMaterial());
	}
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, FVector::ZeroVector);

	if (!IsWounded)
	{
		BlockMesh->SetMaterial(0, CurrentBlock.GetWoundedMaterial());
		IsWounded = true;
	}
	else
	{
		OnBrickDeath.Broadcast();
		Destroy();
	}
}