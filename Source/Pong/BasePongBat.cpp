// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePongBat.h"
#include "Components/BoxComponent.h"


// Sets default values
ABasePongBat::ABasePongBat()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bat hit Box"));
	MyCollider->SetBoxExtent(FVector(64, 32, 128));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePongBat::BeginPlay()
{
	Super::BeginPlay();
	MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize()/2);
	
}

// Called every frame
void ABasePongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

