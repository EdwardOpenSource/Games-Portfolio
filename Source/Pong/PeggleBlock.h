// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PeggleBlock.generated.h"

UCLASS()
class PONG_API APeggleBlock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APeggleBlock();
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	virtual void OnConstruction(const FTransform& Transform) override;
	void DestroyThisObject();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle DestroyTimer;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



private:


};
