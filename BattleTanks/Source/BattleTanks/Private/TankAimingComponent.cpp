// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();

}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
	FiringState = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}

	else
	{
		FiringState = EFiringStatus::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving()
{

	if (!ensure(Barrel))
	{
		return false;
	}

	auto CurrentVector = Barrel->GetForwardVector();
	return !CurrentVector.Equals(AimDirection,0.01f);

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{	

	if (!ensure(Barrel))
	{
		UE_LOG(LogTemp, Error, TEXT("NO BARREL"));
		return;
	}
	if (!ensure(Turret))
	{
		UE_LOG(LogTemp, Error, TEXT("NO Turret"));
		return;
	}


	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, 
		LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}


}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}


	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}

void UTankAimingComponent::Fire()
{

	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming)
	{

		if (!ensure(Barrel))
		{
			return;
		}

		if (!ensure(Projectile_BP))
		{
			return;
		}


		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile_BP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		RoundsLeft -= 1;
	}

}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

