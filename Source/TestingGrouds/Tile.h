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
	void PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius = 300, int32 MinSpawnNumber = 1, int32 MaxSpawnNumber = 1, float MinScale = 1, float MaxScale = 1);

private:	
	bool CanSpawnAtLocation(FVector Location, float Radius);
	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float RotationYaw = 0, float Scale = 1);
	bool FindEmptyLocation(FVector &OutLocation, float Radius);
	
};
