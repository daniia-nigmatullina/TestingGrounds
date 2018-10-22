// Fill out your copyright notice in the Description page of Project Settings.

#include "GrassComponent.h"

UGrassComponent::UGrassComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();
	for (size_t i = 0; i < SpawnCount; i++)
	{
		SpawnGrass();
	}
}

void UGrassComponent::SpawnGrass()
{
	FVector Location = FMath::RandPointInBox(SpawnBounds);
	AddInstance(FTransform(Location));
}
