#pragma once
#include "CoreMinimal.h"
#include "MovingPlatform.h"
#include "OppositeMovingPlatform.generated.h"

UCLASS()
class PONG_API AOppositeMovingPlatform : public AMovingPlatform
{
	GENERATED_BODY()

public:
	AOppositeMovingPlatform();

protected:
	virtual void Tick(float DeltaTime) override;
};
