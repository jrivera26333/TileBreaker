// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStruct.h"
#include "Block.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrickDeath);

UCLASS()
class TILEBREAKER_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnHit();
	FOnBrickDeath OnBrickDeath;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UUDA_BlockContainer* BallDataCollection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* BlockMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USoundCue* HitSound;

	struct FTileStruct CurrentBlock;

	bool IsWounded = false;
};
