// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerrController.generated.h" //Must be the last include


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerrController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const; 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world 

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	void AimTowardsCrosshair();
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
	 
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXPosition = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYPosition = 0.33;


	
};
