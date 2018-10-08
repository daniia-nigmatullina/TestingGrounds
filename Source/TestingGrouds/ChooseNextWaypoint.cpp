// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRoute->GetTargetPoints();
	if (PatrolPoints.Num() == 0) { return EBTNodeResult::Failed; }
	if (Index >= PatrolPoints.Num()) { return EBTNodeResult::Failed; }
	
	auto Waypoint = PatrolPoints[Index];
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoint);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	

	//UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *Name);
	
	return EBTNodeResult::Succeeded;
}
