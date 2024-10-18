// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MariogameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AMariogameMode : public AGameModeBase
{
	GENERATED_BODY()
	inline static int PlayerScore;
public:
	UFUNCTION(BlueprintCallable)
	void ResetScore();
	UFUNCTION()
	static void AddScore(int ScoreToAdd);
	UFUNCTION(BlueprintCallable)
	int GetScore();
};
