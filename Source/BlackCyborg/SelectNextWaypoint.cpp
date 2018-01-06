// Fill out your copyright notice in the Description page of Project Settings.

#include "SelectNextWaypoint.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PatrollingComponent.h"

USelectNextWaypoint::USelectNextWaypoint() { }

EBTNodeResult::Type USelectNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the way points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	UPatrollingComponent* PatrollingCom = ControlledPawn->FindComponentByClass<UPatrollingComponent>();
	if (!ensure(PatrollingCom)) return EBTNodeResult::Type::Failed;

	TArray<AActor*>ProtrolPointsCPP = PatrollingCom->GetPatrolPoints();
	if (ProtrolPointsCPP.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Patrolling Guard is missing 'Patrol Points': %s"), *ControlledPawn->GetName())
		return EBTNodeResult::Type::Failed;
	}

	// Set the next waypoint
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	auto IndexValue = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	Blackboard->SetValueAsObject(NextWaypoint.SelectedKeyName, ProtrolPointsCPP[IndexValue]);

	// Cycle the index
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, (IndexValue + 1) % ProtrolPointsCPP.Num());

	// UE_LOG(LogTemp, Warning, TEXT("Index Value: %i"), IndexValue)
	return EBTNodeResult::Type::Succeeded;
}



