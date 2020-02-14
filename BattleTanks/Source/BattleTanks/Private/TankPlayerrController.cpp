// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankPlayerrController.h"


void ATankPlayerrController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller: %s"), *(ControlledTank->GetName()) );
	}


	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin PLay"));
}

ATank* ATankPlayerrController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerrController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim towards the crosshair.
	AimTowardsCrosshair();

	//UE_LOG(LogTemp, Warning, TEXT("TankPlayerController ticking"));
}


bool ATankPlayerrController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldPosition; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldPosition, LookDirection);
}

void ATankPlayerrController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return; 
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) 
	{
		GetControlledTank()->AimAt(HitLocation);
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
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *(LookDirection.ToString()));

		GetLookVectorHitLocation(LookDirection, HitLocation);

	}


	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *(ScreenLocation.ToString()));


	//De-project the screen position of the cursor to a world direction

	//Line-trace along that look direction and see what we hit (up to a maximum range)

	return true;
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