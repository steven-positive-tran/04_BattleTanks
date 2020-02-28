// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerrController.h"


void ATankPlayerrController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponenet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponenet))
	{
		return;
	}
	FoundAimingComponent(AimingComponenet);
}


void ATankPlayerrController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim towards the crosshair.
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController ticking"));
}

void ATankPlayerrController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerrController::OnPossedTankDeath);
	}
}

void ATankPlayerrController::OnPossedTankDeath()
{
	StartSpectatingOnly();
}



bool ATankPlayerrController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldPosition; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldPosition, LookDirection);
}

void ATankPlayerrController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}

	auto AimingComponenet = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponenet))
	{
		return; 
	}
	
	FVector HitLocation; //Out Parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		AimingComponenet->AimAt(HitLocation);
	}


}

bool ATankPlayerrController::GetSightRayHitLocation(FVector& HitLocation) const
{

	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXPosition, ViewportSizeY * CrosshairYPosition);


	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);

	}

	return false;
}

bool ATankPlayerrController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	//10 km
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0);
		return false;
	}
}
