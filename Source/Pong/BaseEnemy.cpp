// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseEnemy.h"
#include"Mario.h"
#include "PaperCharacter.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));

	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Body"));

	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));

	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Detector"));

	HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Head Detector"));

	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent); 
	LeftTrigger->SetupAttachment(RootComponent);
    RightTrigger->SetupAttachment(RootComponent); 
	HeadTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	BounceForce = 10000;

	Super::BeginPlay();
	MyBodyCollider->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnCollision);
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHeadOverlap);
}

void ABaseEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		Destroy();
	}
}
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}
}

