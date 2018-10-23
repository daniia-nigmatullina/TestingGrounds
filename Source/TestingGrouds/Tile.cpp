// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "AI/Navigation/NavigationSystem.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtent = FVector(0, -2000, 0);
	MaxExtent = FVector(4000, 2000, 0);
	NavigationBoundsOffset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if ((Pool != nullptr) && (NavMeshBoundsVolume != nullptr))
	{
		Pool->Return(NavMeshBoundsVolume);
	}
}

void ATile::SetPool(UActorPool * InPool)
{
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (!NavMeshBoundsVolume) { return; }

	FVector Location = GetActorLocation() + NavigationBoundsOffset; 

	NavMeshBoundsVolume->SetActorLocation(Location);
	GetWorld()->GetNavigationSystem()->Build();
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, float Radius, int32 MinSpawnNumber, int32 MaxSpawnNumber, float MinScale, float MaxScale)
{
	RandomlyPlaceActors(ToSpawn, Radius, MinSpawnNumber, MaxSpawnNumber, MinScale, MaxScale);
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, float Radius, int32 MinSpawnNumber, int32 MaxSpawnNumber)
{
	RandomlyPlaceActors(ToSpawn, Radius, MinSpawnNumber, MaxSpawnNumber, 1, 1);
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnParams& SpawnParams)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
	if (!SpawnedActor) { return; }
	SpawnedActor->SetActorRelativeLocation(SpawnParams.Location);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SetActorRotation(FRotator(0, SpawnParams.RotationYaw, 0));
	SpawnedActor->SetActorScale3D(FVector(SpawnParams.UniformScale));
}

void ATile::PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnParams & SpawnParams)
{
	FVector Location = SpawnParams.Location;
	FRotator Rotation(0, SpawnParams.RotationYaw, 0);
	APawn* SpawnedActor = GetWorld()->SpawnActor<APawn>(ToSpawn, Location, Rotation);
	if (!SpawnedActor) { return; }
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpawnedActor->SpawnDefaultController();
	SpawnedActor->Tags.Add(FName("Guard"));
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);

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

template<class T>
void ATile::RandomlyPlaceActors(TSubclassOf<T> ToSpawn, float Radius, int32 MinSpawnNumber, int32 MaxSpawnNumber, float MinScale, float MaxScale)
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawnNumber, MaxSpawnNumber);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FSpawnParams SpawnParams;

		SpawnParams.UniformScale = FMath::RandRange(MinScale, MaxScale);
		Radius = Radius * SpawnParams.UniformScale;

		if (FindEmptyLocation(SpawnParams.Location, Radius))
		{
			SpawnParams.RotationYaw = FMath::RandRange(-180, 180);

			PlaceActor(ToSpawn, SpawnParams);
		}
	}
}