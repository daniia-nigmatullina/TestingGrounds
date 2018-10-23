// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

USTRUCT()
struct FSpawnParams
{
	GENERATED_USTRUCT_BODY()
	FVector Location;
	float RotationYaw;
	float UniformScale;
};

UCLASS()
class TESTINGGROUDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();

	UFUNCTION(BlueprintCallable, Category = Pool)
	void SetPool(UActorPool* InPool);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category=Setup)
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FVector MaxExtent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category=Tile)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius = 300, int32 MinSpawnNumber = 1, int32 MaxSpawnNumber = 1, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = Tile)
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius = 300, int32 MinSpawnNumber = 1, int32 MaxSpawnNumber = 1);

private:	
	const int32 MAX_ATTEMPTS = 100;

	bool CanSpawnAtLocation(FVector Location, float Radius);
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	template <class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius = 300, int32 MinSpawnNumber = 1, int32 MaxSpawnNumber = 1, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnParams& SpawnParams);
	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnParams& SpawnParams);

	UActorPool* Pool;
	AActor* NavMeshBoundsVolume = nullptr;
	void PositionNavMeshBoundsVolume();

};
