// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Block.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TileBreakerGameModeBase.h"
#include "Engine/EngineTypes.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ball"));
	RootComponent = BallMesh;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	//Subscribing to minus life events
	ATileBreakerGameModeBase* TileBreakerGameModeBase = Cast<ATileBreakerGameModeBase>(UGameplayStatics::GetGameMode(this));
	TileBreakerGameModeBase->OnBallReset.AddDynamic(this, &ABall::ResetPosition);
	
	ResetPosition();
	//BallMesh->SetSimulatePhysics(true);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector VelocityVector = BallMesh->GetComponentVelocity();
	float Magnitude = BallMesh->GetComponentVelocity().Size();
	FVector UnitVector = VelocityVector / Magnitude;

	BallMesh->AddImpulse(UnitVector * 100000);
	ABlock* HitBlock = Cast<ABlock>(OtherActor);

	if (IsValid(HitBlock))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Block!"));
		HitBlock->OnHit();
	}
}

void ABall::ResetPosition()
{
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	AttachToComponent(UGameplayStatics::GetPlayerPawn(this, 0)->GetRootComponent(), TransformRules, "Ball_Restart");
}