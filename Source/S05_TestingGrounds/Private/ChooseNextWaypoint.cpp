// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	/// Get the patrol route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; };

	///Warn about ampty patrol points
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"));
		return EBTNodeResult::Failed;
	};

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
