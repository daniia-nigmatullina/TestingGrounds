// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestingGroundsCharacter.generated.h"

UCLASS()
class TESTINGGROUDS_API ATestingGroundsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATestingGroundsCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void UnPossessed() override;

	UFUNCTION(BlueprintCallable, Category=Firing)
	void PullTrigger();

protected:
	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* FP_Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf <class AGun> GunBlueprint;
	
	class AGun* Gun = nullptr;
};
