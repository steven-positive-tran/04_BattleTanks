// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float AimDirection)
{

	//UE_LOG(LogTemp, Warning, TEXT("%f"), AimDirection);

	AimDirection = FMath::Clamp<float>(AimDirection, -1, 1);
	auto RotationChange = AimDirection * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, Rotation, 0));

	//UE_LOG(LogTemp, Warning, TEXT("Turret is Rotating"));

}