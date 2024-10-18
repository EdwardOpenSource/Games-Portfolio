// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "BreakoutBat.h"
#include "BreakoutBrick.h"
// Sets default values
ABreakoutBall::ABreakoutBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball hit Box"));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();
	BallHalfWidth = MySprite->Bounds.GetBox().GetSize().X / 2;//Get the ball width from the sprite
	MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth, BallHalfWidth));
	MyVelocity = FVector(300, 0, 300);
	AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	UCameraComponent* GameCameraComponent = Cast<ACameraActor>(GameCamera)->GetCameraComponent();
	HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
	HalfPlayFieldWidth = (GameCameraComponent->OrthoWidth / 2);
	BallSpeed = 300;
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakoutBall::OnCollision);

}

// Called every frame
void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

	if (MyUpdatedLocation.Z + BallHalfWidth > HalfPlayFieldHeight)
	{
		MyVelocity.Z = -BallSpeed;// Magic number (Bad)
	}
	else if (MyUpdatedLocation.Z - BallHalfWidth < -HalfPlayFieldHeight)
	{
		MyVelocity.Z = BallSpeed;// Magic number (Bad)	
	}
	if (MyUpdatedLocation.X + BallHalfWidth > HalfPlayFieldWidth)
	{
		MyVelocity.X = -BallSpeed;// Magic number (Bad)
	}
	else if (MyUpdatedLocation.X - BallHalfWidth < -HalfPlayFieldWidth)
	{
		MyVelocity.X = BallSpeed;// Magic number (Bad)	
	}
	if (MyUpdatedLocation.X < -HalfPlayFieldWidth || MyUpdatedLocation.X > HalfPlayFieldWidth)
	{
		// Reset the ball's position to the center of the screen
		MyUpdatedLocation = FVector(0, 0, 0);

		// Reverse the ball's horizontal velocity to continue its trajectory
	   /* MyVelocity.X = -MyVelocity.X;*/
	}
	SetActorLocation(MyUpdatedLocation, false, NULL, ETeleportType::TeleportPhysics);
}


void ABreakoutBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABreakoutBat::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT"));
		FVector BatPosition = GetActorLocation();
		MyVelocity.Z = BallSpeed;
	}
	else if (OtherActor->IsA(ABreakoutBrick::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT A BRICK"));
		//Deflect Ball
		FVector HitDirection = GetActorLocation() - OtherActor->GetActorLocation();
		HitDirection.Normalize();
		if (abs(HitDirection.X) > abs(HitDirection.Z))
		{
			if (HitDirection.X > 0)
			{
				MyVelocity.X = BallSpeed;
			}
			else if (HitDirection.X < 0)
			{
				MyVelocity.X = -BallSpeed;
			}
		}
		else
		{
			if (HitDirection.Z > 0)
			{
				MyVelocity.Z = BallSpeed;
			}
			else if (HitDirection.Z < 0)
			{
				MyVelocity.Z = -BallSpeed;
			}
		}


		OtherActor->Destroy();//Destroy Brick
	}
}