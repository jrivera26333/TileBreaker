// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Ball.h"
#include "TileBreakerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

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

	ATileBreakerGameModeBase* TileBreakerGameModeBase = Cast<ATileBreakerGameModeBase>(UGameplayStatics::GetGameMode(this));
	TileBreakerGameModeBase->OnBallReset.AddDynamic(this, &APaddlePawn::ResetPosition);
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
	//if(HasLaunchedBall)
		AddMovementInput(FVector::LeftVector, movementScaler);
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
	UPaperSpriteComponent* PaperSprite = Cast<UPaperSpriteComponent>(CurrentBall->GetRootComponent());
	if (IsValid(PaperSprite) && !HasLaunchedBall)
	{
		PaperSprite->SetSimulatePhysics(true);
		PaperSprite->AddImpulse(FVector::UpVector * 100000);
		HasLaunchedBall = true;
	}
}
