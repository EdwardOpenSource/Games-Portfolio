// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePongBat.generated.h"

UCLASS()
class PONG_API ABasePongBat : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePongBat();
	UPROPERTY(VisibleAnywhere,Category = "My Sprite");
	UPaperSpriteComponent* MySprite;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
