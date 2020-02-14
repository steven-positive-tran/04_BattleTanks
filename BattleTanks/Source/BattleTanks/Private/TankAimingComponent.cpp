// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{	

	if (!Barrel)
	{
		UE_LOG(LogTemp, Error, TEXT("NO BARREL"));
		return;
	}
	if (!Turret)
	{
		UE_LOG(LogTemp, Error, TEXT("NO Turret"));
		return;
	}


	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, 
		LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto Time = GetWorld()->GetTimeSeconds();
		MoveBarrelTowards(AimDirection);
		//MoveTurretDirection(HitLocation.Rotation());
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *(HitLocation.Rotation().ToString()));

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingComponent::MoveTurretDirection(FRotator Direction)
{
	//auto HitX = Direction.X;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *TurretLocation.ToString());
	//Turret->Rotate(Direction.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{

	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;

}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}

