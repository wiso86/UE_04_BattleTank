// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"

#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

}

void ATank::AimAt(FVector HitLocation)
{
	// TODO: Change the aiming component so it can be called from somewhere else
	//TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	// TODO: Change the aiming component so it can be fired from somewhere else

	//bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//if (Barrel && IsReloaded)
	//{
	//	// Spawn a projectile at the socket location of the barrel
	//	auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//	auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
	//	auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

	//	NewProjectile->LaunchProjectile(LaunchSpeed);
	//	LastFireTime = FPlatformTime::Seconds();
	//}
}