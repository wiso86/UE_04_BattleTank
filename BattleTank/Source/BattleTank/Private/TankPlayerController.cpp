// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto possesedTank = GetControlledTank();

	if (possesedTank)
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *possesedTank->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"))
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimToCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimToCrosshair() const
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	// Get world location through crosshair (linetrace)
	if (GetSightRayHilLocation(HitLocation)) {
		// If it hits the landscape
		// Tell controlled tank to aim at this point
	}
}

bool ATankPlayerController::GetSightRayHilLocation(FVector & HitLocation) const
{
	// Find the corsshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection, CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection)) 
	{
		FHitResult HitResult;
		FVector EndTrace = CameraWorldLocation + (WorldDirection * 1000);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraWorldLocation, EndTrace, ECC_WorldStatic))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor name: %s"), *HitResult.GetActor()->GetName());
		}
	}
	
	// If it hits the landscape
		// Set HitLocation to its position and return true
	// If not
		// Return false

	return false;
}
