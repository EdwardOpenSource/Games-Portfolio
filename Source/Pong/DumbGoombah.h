// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "DumbGoombah.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ADumbGoombah : public ABaseEnemy
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay();
	float EnemyHorizontalAcceleration= 10000;
	float EnemyMaxSpeed =10000;
public:
	
	virtual void Tick(float DeltaTime) override;
	

};
