// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBallLauncher.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APeggleBallLauncher::APeggleBallLauncher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprites"));
	RootComponent = MySprite;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void APeggleBallLauncher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MySprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MySprite->TranslucencySortPriority = 3;

}
void APeggleBallLauncher::MovePlayer(float input)
{
	SetActorRotation(GetActorRotation() + FRotator(1 * input, 0, 0));
}
// Called when the game starts or when spawned
void APeggleBallLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}
void APeggleBallLauncher::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Firing!"));  
	AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(BallBPClass, GetActorLocation(), GetActorRotation());
	FVector ShotDirection = GetActorUpVector() *= -1;
	SpawnedBall->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * ShotPower);
}

// Called every frame
void APeggleBallLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APeggleBallLauncher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("Horizontal", this, &APeggleBallLauncher::MovePlayer);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APeggleBallLauncher::Fire);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

