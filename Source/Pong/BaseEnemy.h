// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

UCLASS()
class PONG_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "My Sprite")
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	UPROPERTY(VisibleAnywhere, Category = "Triggers")
	class UBoxComponent* LeftTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Triggers")
	class UBoxComponent* RightTrigger;
	UPROPERTY(VisibleAnywhere, Category = "Triggers")
	class UBoxComponent* HeadTrigger;
	float BounceForce = 10000;
	
public:	
	UFUNCTION()
	void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
