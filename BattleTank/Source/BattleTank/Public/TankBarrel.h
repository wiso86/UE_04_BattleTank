// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 for max downward movement, +1 for max upward movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly)
	float MaxDegreesPerSecond = 20.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxElevationDegrees = 40.0f;

	UPROPERTY(EditDefaultsOnly)
	float MinElevationDegrees = 0.0f;

};
