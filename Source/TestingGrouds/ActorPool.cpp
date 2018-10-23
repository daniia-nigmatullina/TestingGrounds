// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"

UActorPool::UActorPool()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AActor * UActorPool::Checkout()
{
	if (Pool.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Enought Actors in Pool"));
		return nullptr;
	}

	auto PoppedActor = Pool.Pop();

	UE_LOG(LogTemp, Warning, TEXT("Checkout to Tile from Pool: %s"), *(PoppedActor->GetName()));

	return PoppedActor;
}

void UActorPool::Return(AActor * ActorToReturn)
{
	if (!ActorToReturn) { return; }

	UE_LOG(LogTemp, Warning, TEXT("Returned to Pool: %s"), *(ActorToReturn->GetName()));

	this->Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (!ActorToAdd) {return; }
	UE_LOG(LogTemp, Warning, TEXT("Added to Pool: %s"), *(ActorToAdd->GetName()));
	
	Pool.Push(ActorToAdd);
}
