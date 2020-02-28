// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h" 
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Received!"))

	auto Tank = GetPawn();

	if (!ensure(Tank))
	{
		return;
	}

	Tank->DetachFromControllerPendingDestroy();

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
