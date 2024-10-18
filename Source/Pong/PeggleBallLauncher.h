// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "PeggleBallLauncher.generated.h"

UCLASS()
class PONG_API APeggleBallLauncher : public APawn
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TSubclassOf<AActor> BallBPClass;

public:
	// Sets default values for this pawn's properties
	APeggleBallLauncher();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Fire();
	void MovePlayer(float input);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float ShotPower = 40000;


};
