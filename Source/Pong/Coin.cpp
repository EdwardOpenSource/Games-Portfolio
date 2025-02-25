// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "PaperSpriteComponent.h"
#include"MariogameMode.h"
// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MyImage"));
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ACoin::BeginOverlap);
}

void ACoin::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Coin Hit!"));
	AMariogameMode::AddScore(1);
	Destroy();
}
// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

