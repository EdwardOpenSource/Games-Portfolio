// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "BreakoutBat.generated.h"

/**
 *
 */
UCLASS()
	class PONG_API ABreakoutBat : public ABasePongBat
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Tick(float DeltaTime);
	void MovePlayer(float input);
	//void Tick(float DeltaTime) override;
	FVector TemporaryPosition;
	
};
