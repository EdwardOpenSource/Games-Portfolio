// Fill out your copyright notice in the Description page of Project Settings.



#include "Mario.h"
#include"MariogameMode.h"
#include"Bullet.h"
#include "PaperflipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMario::AMario()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MarioBodySprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MarioSpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));
	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera->SetupAttachment(MySpringArm);
	
	
	
}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
	Super::BeginPlay();
	MyBodyCollider->OnComponentHit.AddDynamic(this, &AMario::OnCollision);
	bIsJumping = false;
	bMarioisDead = false;
	CurrentAnimationState = MarioAnimationState::AS_IDLE;
	OldAnimationState = MarioAnimationState::AS_EMPTY;
	ProcessAnimStateMachine();

	

	
}
void AMario::MovePlayerHorizontal(float value)
{
	MyBodyCollider->AddForce(FVector(1,0,0)*value*PlayerAcceleration,NAME_None,true);
	//UE_LOG(LogTemp, Warning, TEXT("I have been Summoned!"));

}
void AMario::Jump()
{
	if (!bIsJumping)
	{ 
		MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);
		bIsJumping = true;
	}
	
	
}
// Called every frame
void AMario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//clamp maximum speed in x direction to player speed
	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
	
	IdentifyAnimStates();
	ProcessAnimStateMachine();
}

// Called to bind functionality to input
void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &AMario::MovePlayerHorizontal);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMario::Jump);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &AMario::Shoot);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

	
void AMario::IdentifyAnimStates()
{
	OldAnimationState = CurrentAnimationState;

	//Get horizontal speed and change state based on that speed
	float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;
	if (CurrentSpeed > 5)
	{
		CurrentAnimationState = MarioAnimationState::AS_WALKING_RIGHT;
	}
	else if (CurrentSpeed < -5)
	{
		CurrentAnimationState = MarioAnimationState::AS_WALKING_LEFT;
	}
	else
	{
		CurrentAnimationState = MarioAnimationState::AS_IDLE;
	}
	//if mario is dead
	if (bMarioisDead == true)
	{
		CurrentAnimationState = MarioAnimationState::AS_DEAD;
	}
	if (bIsShooting)
	{
		CurrentAnimationState = MarioAnimationState::AS_SHOOTING_RIGHT;
	}
}

void AMario::ProcessAnimStateMachine()
{
	//check if the animation state has changed 
	if (CurrentAnimationState == OldAnimationState)
	{
		return;
	}
	//update the sprite based on the state
	switch (CurrentAnimationState)
	{
	case MarioAnimationState::AS_IDLE:
	
		MySprite->SetFlipbook(Flipbook_Idle);
		return;
	
	case MarioAnimationState::AS_WALKING_RIGHT:
	
		MySprite->SetFlipbook(Flipbook_WalkingRight);
		MySprite->SetRelativeRotation(FRotator(0, 0, 0));
		return;
	
	case MarioAnimationState::AS_WALKING_LEFT:
	
		MySprite->SetFlipbook(Flipbook_WalkingRight);
		MySprite->SetRelativeRotation(FRotator(0, 180, 0));
		return;
	case MarioAnimationState::AS_DEAD:
		MySprite->SetFlipbook(Flipbook_Dead);
		UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
		return;
	case MarioAnimationState::AS_SHOOTING_RIGHT:
		MySprite->SetFlipbook(Flipbook_Shooting);
		return;
	}

}
void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		bIsJumping = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Mario hit the floor"));
	
}
void AMario::BounceMario(float force)
{
	MyBodyCollider->AddImpulse(FVector(0, 0, force));
}
void AMario::KillMario()
{
	UE_LOG(LogTemp, Warning, TEXT("Mario is Dead"));
	CurrentAnimationState = MarioAnimationState::AS_DEAD;
	ProcessAnimStateMachine();
	bMarioisDead = true;
	
	
}
void AMario::Shoot()
{
	//// Create a new bullet
 //    AActor* SpawnedBullet = GetWorld()->SpawnActor<AActor>(BPBullet, GetActorLocation(), GetActorRotation());
	// FVector ShotDirection = GetActorForwardVector();
	////// Set the bullet's velocity

	//SpawnedBullet->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * BulletSpeed);

	///// Set the bullet's owner so it doesn't collide with Mario
	//SpawnedBullet->SetOwner(this);
	 // Create a new bullet
	AActor* SpawnedBullet = GetWorld()->SpawnActor<AActor>(BPBullet, GetActorLocation(), GetActorRotation());

	if (SpawnedBullet) // Check if SpawnedBullet is not null
	{
	 UPaperSpriteComponent* BulletSpriteComponent = SpawnedBullet->GetComponentByClass<UPaperSpriteComponent>();

	if (BulletSpriteComponent) // Check if BulletSpriteComponent is not null
	{
	//		// Set the bullet's velocity
	     FVector ShotDirection = GetActorForwardVector();
	      BulletSpriteComponent->AddImpulse(ShotDirection * BulletSpeed);

		// Set the bullet's owner so it doesn't collide with Mario
			SpawnedBullet->SetOwner(this);
		}
	}
}


