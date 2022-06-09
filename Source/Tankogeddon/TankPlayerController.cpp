// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);

	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankPlayerController::Fire);

	InputComponent->BindAction("FireSpecial", EInputEvent::IE_Pressed, this, &ATankPlayerController::FireSpecial);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePosition, mouseDirection);

	FVector PawnPosition = TankPawn->GetActorLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector dir = MousePosition - PawnPosition;
	dir.Normalize();

	MousePosition = PawnPosition + dir * 1000;

	DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Green, false, 0.1f, 0, 5);
}


void ATankPlayerController::MoveForward(float Value)
{
	TankPawn->MoveForward(Value);
}

void ATankPlayerController::RotateRight(float Value)
{
	TankPawn->RotateRight(Value);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}
