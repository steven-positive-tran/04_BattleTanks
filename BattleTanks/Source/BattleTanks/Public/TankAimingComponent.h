// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankAimingComponent.generated.h"


// Forward Declaration
class UTankBarrel; 
class UTankTurret;
// Hold parameters for barrel's properties and Elevate method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr; 

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretDirection(FRotator Direction);

		
};
