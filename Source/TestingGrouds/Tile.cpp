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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, int32 MinToSpawn, int32 MaxToSpawn)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	
	int32 NumberToSpawn = FMath::RandRange(MinToSpawn, MaxToSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(Bounds);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
		SpawnedActor->SetActorRelativeLocation(SpawnLocation);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		
		CastSphere(SpawnLocation, 300);
	}
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		Location, 
		Location, 
		FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);

	FColor Color;
	if (HasHit)
	{
		Color = FColor::Red;
	}
	else
	{
		Color = FColor::Green;
	}

	//DrawDebugSphere(GetWorld(), Location, Radius, 16, Color, true, 100);
	DrawDebugCapsule(GetWorld(), Location, 500, Radius, FQuat::Identity, Color, true, 100);

	return HasHit;
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

