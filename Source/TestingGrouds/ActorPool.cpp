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

	return  Pool.Pop();
}

void UActorPool::Return(AActor * ActorToReturn)
{
	if (ActorToReturn == nullptr) { return; }
	this->Add(ActorToReturn);
}

void UActorPool::Add(AActor * ActorToAdd)
{
	if (!ActorToAdd) {return; }
	Pool.Push(ActorToAdd);
}
