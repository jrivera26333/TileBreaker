// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//RootComponent = RootSceneComponent;

	BallMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Ball"));
	RootComponent = BallMesh;
	//BallMesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnHit);

	ResetPosition();
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

	UE_LOG(LogTemp, Warning, TEXT("Ball Velocity: %s"), *UnitVector.ToString());
	
	BallMesh->AddImpulse(UnitVector * 100000);
}

void ABall::ResetPosition()
{
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	AttachToComponent(UGameplayStatics::GetPlayerPawn(this, 0)->GetRootComponent(), TransformRules, "Ball_Restart");
}