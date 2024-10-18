// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BreakoutBat.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Math/UnitConversion.h"
#include "BreakoutBall.h"
//#include "BreakoutBat.generated.h"

void ABreakoutBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(5*input, 0, 0 ));

}
void ABreakoutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &ABreakoutBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ABreakoutBat::Tick(float DeltaTime)
{
	FVector BatLocation = GetActorLocation();
	
	FVector NewLocation = GetActorLocation();
	/*NewLocation.Z = FMath::Clamp(NewLocation.Z, -2048, 2048);*/
	NewLocation.X = FMath::Clamp(NewLocation.X, -300+64,300-64);
	SetActorLocation(NewLocation);
}
