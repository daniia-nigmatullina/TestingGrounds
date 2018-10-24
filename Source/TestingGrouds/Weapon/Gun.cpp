// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "BallProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	
	RootComponent = FP_Gun;

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Fire()
{
	if (!ensure(ProjectileClass)) { return; }

	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = FP_MuzzleLocation->GetComponentRotation();
		const FVector SpawnLocation = FP_MuzzleLocation->GetComponentLocation();
		World->SpawnActor<ABallProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	}
	
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FirstPersonFireAnimation && AnimInstance_1P)
	{
		AnimInstance_1P->Montage_Play(FirstPersonFireAnimation, 1.f);
	}

	if (ThirdPersonFireAnimation && AnimInstance_3P)
	{
		AnimInstance_3P->Montage_Play(ThirdPersonFireAnimation, 1.f);
	}

}
