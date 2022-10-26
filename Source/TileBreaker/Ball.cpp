// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Block.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrickGameInstance.h"
#include "Engine/EngineTypes.h"
#include "Components/SphereComponent.h"
#include "DeathArea.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = SphereCollider;

	BallMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ball"));
	BallMesh->SetupAttachment(SphereCollider);;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	SubscribeToOnDeath();
	ResetPosition();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
void ABall::SubscribeToOnDeath()
{
	ADeathArea* DeathArea = Cast<ADeathArea>(UGameplayStatics::GetActorOfClass(this, ADeathArea::StaticClass()));

	if (IsValid(DeathArea))
	{
		DeathArea->OnBallDeath.AddDynamic(this, &ABall::DestroyBall);
	}

}

void ABall::DestroyBall()
{	
	Destroy();
}

void ABall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
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