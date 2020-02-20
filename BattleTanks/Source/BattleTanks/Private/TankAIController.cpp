// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if(ensure(PlayerTank && ControlledTank))
	{ 
		MoveToActor(PlayerTank, AccpetanceRadius); //TO DO CHECK IF RADIUS IS IN CENTIMETERS
 
		ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());


		//if aimed or locked 
		if (ControlledTank->FindComponentByClass<UTankAimingComponent>()->GetFiringStatus() == EFiringStatus::Locked)
		{
			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
		}
	}
}
