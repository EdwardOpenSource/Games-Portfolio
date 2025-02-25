// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPongBat.h"
#include "PongBall.h"
#include "Kismet/GameplayStatics.h"

void AAIPongBat::BeginPlay()
{
	Super::BeginPlay();//runs the base begin play in our class
	TheBall = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());

}
void AAIPongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);//runs the tick method in our base class
	if (GetActorLocation().Z > TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation()+FVector(0,0,-8));

	}
	if (GetActorLocation().Z < TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, 8));

	}
}
