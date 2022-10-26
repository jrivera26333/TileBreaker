// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Ball.h"
#include "BrickGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayWidget.h"
#include "DeathArea.h"
#include "PaddlePlayerController.h"


// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaddleSprite"));
	PaddleMesh->SetSimulatePhysics(true);
	RootComponent = PaddleMesh;
}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	CreateBall();
	ResetPosition();

	SubscribeToBallDestroyed();
}

// Called every frame
void APaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LateralMovement", this, &APaddlePawn::MoveXDirection);
	PlayerInputComponent->BindAction("FireBall", IE_Pressed, this, &APaddlePawn::LaunchBall);
}

void APaddlePawn::MoveXDirection(float movementScaler)
{
	if(HasHitPlay)
		AddMovementInput(FVector::LeftVector, movementScaler);
}

void APaddlePawn::SetHasHitPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Play Hit"));
	HasHitPlay = true;
}

void APaddlePawn::SubscribeToBallDestroyed()
{
	ADeathArea* DeathArea = Cast<ADeathArea>(UGameplayStatics::GetActorOfClass(this, ADeathArea::StaticClass()));

	if (IsValid(DeathArea))
	{
		DeathArea->OnBallDeath.AddDynamic(this, &APaddlePawn::ResetPosition);
	}
}

void APaddlePawn::CreateBall()
{
	CurrentBall = GetWorld()->SpawnActor<ABall>(PongBallClass);
}

void APaddlePawn::ResetPosition()
{
	PaddleMesh->SetWorldLocation(FVector::ZeroVector);
	HasLaunchedBall = false;
}

void APaddlePawn::LaunchBall()
{
	if (!HasLaunchedBall && HasHitPlay)
	{
		auto ProjectileMovement = Cast<UProjectileMovementComponent>(CurrentBall->GetComponentByClass(UProjectileMovementComponent::StaticClass()));
		if (IsValid(ProjectileMovement))
		{
			ProjectileMovement->Activate();
			FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);

			CurrentBall->DetachFromActor(Rules);
			UE_LOG(LogTemp, Warning, TEXT("Valid!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Valid!"));
		}

		HasLaunchedBall = true;
	}
}
