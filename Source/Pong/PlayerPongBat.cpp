// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPongBat.h"

#include "Math/UnitConversion.h"

void APlayerPongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Vertical", this, &APlayerPongBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void APlayerPongBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(0, 0, 12 * input));

}

void APlayerPongBat::Tick(float DeltaTime)
{
	FVector BatLocation = GetActorLocation();
	SetActorLocation(BatLocation);
	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X, -2048, 2048);
	NewLocation.Z = FMath::Clamp(NewLocation.Z, ( - (2048 / 1.777) / 2)+128, ((2048 / 1.777) / 2) -128);
	SetActorLocation(NewLocation);
}

