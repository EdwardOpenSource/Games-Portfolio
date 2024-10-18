#include "MovingPlatform.h"
#include "Mario.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

AMovingPlatform::AMovingPlatform()
{
	// Set actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	//sprite component
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;

	// Set speed and direction
	Speed = 50.0f;//initial speed
	Direction = -1;// initial direction from right to left

	

}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	MySprite->OnComponentHit.AddDynamic(this, &AMovingPlatform::OnCollision);//on component hit event is triggered for this sprite when colliding with the player
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the platform
	AddActorLocalOffset(GetActorForwardVector() * Speed * DeltaTime * Direction);//returns the direction which the player is facing
	//direction is either + or - for foward and back on the horizontal axis 
	//then AddActor func moves the actor(ghost/moving platform ) in the direction specified in the constructor
}

void AMovingPlatform::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario(); // initial plan was to kill the player upon collision but it didn't work so the error was it pushed upon collision 
		//so i kept that behavior instead and used it for pushing the player
	}
}
//note - it is a ghost because it collides with the player not the other objects in the level 
