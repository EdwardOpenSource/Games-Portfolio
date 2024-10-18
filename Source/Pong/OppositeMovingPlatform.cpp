#include "OppositeMovingPlatform.h"

AOppositeMovingPlatform::AOppositeMovingPlatform()
{
	// Set the direction to the opposite of the original
	Direction = -Direction;
}

void AOppositeMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the platform in the opposite direction
	AddActorLocalOffset(GetActorForwardVector() * Speed * DeltaTime * Direction);
}
