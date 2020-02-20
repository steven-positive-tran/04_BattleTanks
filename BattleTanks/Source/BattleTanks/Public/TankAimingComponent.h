// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankAimingComponent.generated.h"


//Enums
UENUM()
enum class EFiringStatus : uint8
{
	Locked, Aiming, Reloading, OutOfAmmo
};

// Forward Declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;
// Hold parameters for barrel's properties and Elevate method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BluePrintCallable, Category = Setup)
	void Initialize(UTankBarrel * Barrel, UTankTurret * Turret);
	void AimAt(FVector HitLocation);

	UFUNCTION(BluePrintCallable)
	void Fire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BluePrintCallable)
	int GetRoundsLeft() const;


protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus FiringState = EFiringStatus::Reloading;

private:

	UTankAimingComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsBarrelMoving();
	void MoveBarrelTowards(FVector AimDirection);


	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr; 

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 100000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> Projectile_BP;



	float LastFireTime = 0;
	FVector AimDirection;


	int RoundsLeft = 3;
		
};
