// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerrController.generated.h" //Must be the last include


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerrController : public APlayerController
{
	GENERATED_BODY()


protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);


private:
 

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	//Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world 

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	void AimTowardsCrosshair();
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	
	UFUNCTION()
	void OnPossedTankDeath();

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
	 
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXPosition = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYPosition = 0.33;


	
};
