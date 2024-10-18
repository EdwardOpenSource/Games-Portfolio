// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Mario.generated.h"

UENUM()
enum class MarioAnimationState : uint8
{
	AS_WALKING_RIGHT,
	AS_WALKING_LEFT,
	AS_JUMPING_LEFT,
	AS_IDLE,
	AS_SHOOTING_RIGHT,
	AS_DEAD,
	AS_EMPTY
};

UCLASS()
class PONG_API AMario : public APawn
{
	public:
	// Sets default values for this pawn's properties
	AMario();
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class UCameraComponent* MyCamera;

	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float JumpForce = 30;

	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerAcceleration = 20;
	UPROPERTY(EditAnywhere, Category = "Player Properties")
	float PlayerMaxSpeed = 32;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_WalkingRight;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Idle;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Dead;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Shooting;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	MarioAnimationState CurrentAnimationState;
	UPROPERTY(VisibleAnywhere, Category = "Animations")
	MarioAnimationState OldAnimationState;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MovePlayerHorizontal(float value);
	virtual void Jump();
	void IdentifyAnimStates();
	void ProcessAnimStateMachine();
	bool bIsJumping;
	bool bMarioisDead;
	bool bIsShooting;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void KillMario();
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void BounceMario(float force);
	void Shoot();
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float BulletSpeed = 40000;
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TSubclassOf<AActor> BPBullet;

	
};
