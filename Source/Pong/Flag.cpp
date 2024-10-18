#include "Flag.h"
#include "Mario.h"

AFlag::AFlag()
{
	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
	
}

void AFlag::BeginPlay()
{
	Super::BeginPlay();
}

void AFlag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

