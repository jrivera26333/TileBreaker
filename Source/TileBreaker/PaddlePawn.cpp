// Fill out your copyright notice in the Description page of Project Settings.


#include "PaddlePawn.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Ball.h"
#include "Camera/CameraComponent.h"

// Sets default values
APaddlePawn::APaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaddleSprite"));
	RootComponent = PaddleMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(PaddleCollision);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	CreateBall();
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
}

void APaddlePawn::MoveXDirection(float movementScaler)
{
	AddMovementInput(FVector::LeftVector, movementScaler);
}

void APaddlePawn::CreateBall()
{
	GetWorld()->SpawnActor<ABall>(PongBallClass);
}