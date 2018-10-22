// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent), ClassGroup=(Custom))
class TESTINGGROUDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UGrassComponent();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FBox SpawnBounds;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	int32 SpawnCount;

private:
	void SpawnGrass();
	
};
