// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBrick.h"

// Sets default values
ABreakoutBrick::ABreakoutBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;

}

// Called when the game starts or when spawned
void ABreakoutBrick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakoutBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

