// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if(PlayerTank)
	{ 
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerTank->GetActorLocation().ToString())
		//ControlledTank->Fire();
	}
}
