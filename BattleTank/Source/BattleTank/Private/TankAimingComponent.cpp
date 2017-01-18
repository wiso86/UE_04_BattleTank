// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto TankName = GetOwner()->GetName();
	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// We need to take the values of the shoot direction
	FVector OutLaunchVelocity;
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		AimBarrelTo(AimDirection);
	}
}

void UTankAimingComponent::AimBarrelTo(FVector AimDirection)
{
	auto AimRotator = AimDirection.Rotation();
	auto BarrelRotator = Barrel->GetComponentRotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	// If |Yaw| > 180, we change the direction of the rotation
	auto RawYaw = DeltaRotator.Yaw;
	if (RawYaw > 180.0f)
		RawYaw -= 360.0f;
	else if (RawYaw < -180.0f)
		RawYaw += 360.0f;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(RawYaw);
}

void UTankAimingComponent::Fire()
{
	// TODO: Change the aiming component so it can be fired from somewhere else

	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && IsReloaded)
	{
		// Spawn a projectile at the socket location of the barrel
		auto ProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto ProjectileRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

		NewProjectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
