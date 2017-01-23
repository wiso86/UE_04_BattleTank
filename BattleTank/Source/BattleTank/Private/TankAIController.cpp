// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		auto ControlledAimingComp = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (ensure(ControlledAimingComp)) {
			ControlledAimingComp->AimAt(PlayerTank->GetActorLocation());
			if (ControlledAimingComp->GetFiringState() == EFiringState::Locked) {
				ControlledAimingComp->Fire();
			}
		}
	}
}

