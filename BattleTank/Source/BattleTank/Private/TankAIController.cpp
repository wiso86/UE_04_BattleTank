// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if(PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("AIController finds player tank: %s"), *PlayerTank->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("AIController don't find player tank"))
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

