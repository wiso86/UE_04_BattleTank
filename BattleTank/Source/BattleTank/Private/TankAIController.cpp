// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if(PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("AIController finds player tank: %s"), *PlayerTank->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("AIController don't find player tank"))
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GetControlledTank()) { return; }
	if (!GetPlayerTank()) { return; }
	
	auto PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(PlayerTankLocation);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
		return nullptr;
	return Cast<ATank>(PlayerController->GetPawn());
}

