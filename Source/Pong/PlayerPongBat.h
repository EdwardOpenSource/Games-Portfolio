// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "PlayerPongBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APlayerPongBat : public ABasePongBat
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MovePlayer(float input);
	void Tick(float DeltaTime) override;
};