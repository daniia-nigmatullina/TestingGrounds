// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius, int32 MinSpawnNumber, int32 MaxSpawnNumber, float MinScale, float MaxScale)
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawnNumber, MaxSpawnNumber);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation;

		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		Radius = Radius * RandomScale;

		if (FindEmptyLocation(SpawnLocation, Radius))
		{
			float RandomRotation = FMath::RandRange(-180, 180);

			PlaceActor(ToSpawn, SpawnLocation, RandomRotation, RandomScale);
		}
	}
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, float RotationYaw, float Scale)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	SpawnedActor->SetActorRelativeLocation(Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, RotationYaw, 0));
	SpawnedActor->SetActorScale3D(FVector(Scale, Scale, Scale));
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	
	const int32 MAX_ATTEMPTS = 100;

	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector Location = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(Location, Radius))
		{
			OutLocation = Location;
			return true;
		}
	}
	
	return false;
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FVector GlovalLocation = ActorToWorld().TransformPosition(Location);

	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		GlovalLocation,
		GlovalLocation,
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);

	return !HasHit;
}


// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

