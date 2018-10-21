// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category=Tile)
	void PlaceActor(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn);

private:	
	bool CastSphere(FVector Location, float Radius);
	
	
};
