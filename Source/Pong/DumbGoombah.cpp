// Fill out your copyright notice in the Description page of Project Settings.


#include "DumbGoombah.h"
#include "Components/CapsuleComponent.h"

void ADumbGoombah::BeginPlay()
{
	Super::BeginPlay();
	
}


void ADumbGoombah::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyBodyCollider->AddForce(FVector(1, 0,  0) *EnemyHorizontalAcceleration);
	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}




