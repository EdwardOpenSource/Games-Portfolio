// Fill out your copyright notice in the Description page of Project Settings.


#include "PongBall.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
APongBall::APongBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball hit Box"));
	MyCollider->SetBoxExtent(FVector(32, 32, 32));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);
	PlayerScore = 0;
	AIScore = 0;
}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();
	MyVelocity = FVector(600, 0, 600);
	HalfPlayFieldHeight = (2048 / 1.777) / 2;
	HalfPlayFieldWidth = (2048 / 2);
	PlayerScore = 0;
	AIScore = 0;

	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnCollision);
	
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	 FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity*DeltaTime);

	 if (MyUpdatedLocation.Z > HalfPlayFieldHeight)
	 {
		 MyVelocity.Z = -600;// Magic number (Bad)
	 }
	 else if (MyUpdatedLocation.Z < -HalfPlayFieldHeight)
	 {
		 MyVelocity.Z = 600;// Magic number (Bad)	
	 }
	 if (MyUpdatedLocation.X> HalfPlayFieldWidth)
	 {
		 MyVelocity.X = -600;// Magic number (Bad)
		 AIScore += 1;

		 UE_LOG(LogTemp, Warning, TEXT("AI SCORE: %d"), AIScore);
		 UE_LOG(LogTemp, Warning, TEXT("PLAYER SCORE: %d"), PlayerScore);
	 }
	 else if (MyUpdatedLocation.X < -HalfPlayFieldWidth)
	 {
		 MyVelocity.X = 600;// Magic number (Bad)
		 PlayerScore += 1;

		 UE_LOG(LogTemp, Warning, TEXT("AI SCORE: %d"), AIScore);
		 UE_LOG(LogTemp, Warning, TEXT("PLAYER SCORE: %d"), PlayerScore);
	 }
	 if (MyUpdatedLocation.X < -HalfPlayFieldWidth || MyUpdatedLocation.X > HalfPlayFieldWidth)
	 {
		 // Reset the ball's position to the center of the screen
		 MyUpdatedLocation = FVector(0, 0, 0);

		 // Reverse the ball's horizontal velocity to continue its trajectory
		/* MyVelocity.X = -MyVelocity.X;*/
	 }
	 /*if (MyUpdatedLocation.X < -HalfPlayFieldWidth )
	 {
		 PlayerScore += 1;
		 UE_LOG(LogTemp, Warning, TEXT("AI SCORE: %d"), AIScore);
		 UE_LOG(LogTemp, Warning, TEXT("PLAYER SCORE: %d"), PlayerScore);
     }
	 else if (MyUpdatedLocation.X > HalfPlayFieldWidth)
	 {
		 AIScore += 1;
		 UE_LOG(LogTemp, Warning, TEXT("AI SCORE: %d"), AIScore);
		 UE_LOG(LogTemp, Warning, TEXT("PLAYER SCORE: %d"), PlayerScore);
	 }*/
		 
		 SetActorLocation(MyUpdatedLocation,false,NULL,ETeleportType::TeleportPhysics);

}
void APongBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("I HAVE HIT SOMETHING"));
	FVector BatPosition = GetActorLocation();
	if (BatPosition.X > 0)
	{
		MyVelocity.X = -600;//Magic number
	}
	else if (BatPosition.X < 0)
	{
		MyVelocity.X = 600;//Magic number
	}
}