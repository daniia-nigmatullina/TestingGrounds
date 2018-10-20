// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGroundsCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Weapon/Gun.h"

// Sets default values
ATestingGroundsCharacter::ATestingGroundsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); 
	Camera->bUsePawnControlRotation = true;

	FP_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Mesh"));
	FP_Mesh->SetupAttachment(Camera);
	FP_Mesh->SetOnlyOwnerSee(true);
	FP_Mesh->bCastDynamicShadow = false;
	FP_Mesh->CastShadow = false;
	FP_Mesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FP_Mesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void ATestingGroundsCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

		if (IsPlayerControlled())
		{
			Gun->AttachToComponent(FP_Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		else
		{
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		
		Gun->AnimInstance_1P = FP_Mesh->GetAnimInstance();
		Gun->AnimInstance_3P = GetMesh()->GetAnimInstance();

		if (InputComponent)
		{
			InputComponent->BindAction("Fire", IE_Pressed, this, &ATestingGroundsCharacter::PullTrigger);
		}
	}
}

void ATestingGroundsCharacter::UnPossessed()
{
	Super::UnPossessed();
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}

void ATestingGroundsCharacter::PullTrigger()
{
	if (!ensure(Gun)) { return; }
	Gun->Fire();
}

// Called every frame
void ATestingGroundsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestingGroundsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

