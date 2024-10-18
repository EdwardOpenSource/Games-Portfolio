// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBall.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
APeggleBall::APeggleBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;

}

// Called when the game starts or when spawned
void APeggleBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeggleBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

