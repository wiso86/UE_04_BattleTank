// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimToCrosshair();
}

void ATankPlayerController::AimToCrosshair() const
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;
	// Get world location through crosshair (linetrace)
	if (GetSightRayHilLocation(HitLocation)) {
		// If it hits the landscape
		// Tell the aiming component to aim at this point
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHilLocation(FVector & HitLocation) const
{
	// Find the corsshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection, dummy;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, dummy, WorldDirection))
	{
		return GetLookVectorHitLocation(WorldDirection, HitLocation);
	}
	else
	{
		HitLocation = FVector::ZeroVector;
		return false;
	}
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	// Line trace from the camera in the direction to LookDirection
	FHitResult HitResult;
	FVector CameraWorldLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndTrace = CameraWorldLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraWorldLocation, EndTrace, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector::ZeroVector;
		return false;
	}
}
