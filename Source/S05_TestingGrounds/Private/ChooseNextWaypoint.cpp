// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//TODO protect againts empty patrol routes

	/// Get the patrol points
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	///Set next waypoint
	auto BlacboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlacboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlacboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	///Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlacboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	///UE_LOG(LogTemp, Warning, TEXT("Index: %i"), Index);

	return EBTNodeResult::Succeeded;
}
