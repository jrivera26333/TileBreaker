// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathArea.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADeathArea::ADeathArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = CollisionArea;
}

// Called when the game starts or when spawned
void ADeathArea::BeginPlay()
{
	Super::BeginPlay();

	//Binding Collision
	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &ADeathArea::OnOverlap);
}

// Called every frame
void ADeathArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathArea::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnBallDeath.IsBound())
	{
		OnBallDeath.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Bound!"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Hit Death Area!"));
}