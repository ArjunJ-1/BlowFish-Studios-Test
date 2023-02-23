// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Patrol.h"

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorComp = &OwnerComp;
	if(!BehaviorComp)
		return EBTNodeResult::Failed;

	AAI_Controller* AIController = Cast<AAI_Controller>(BehaviorComp->GetOwner());
	if(!AIController)
		return EBTNodeResult::Failed;

	AIController->RandomlySelectPatrolPoint();
	
	return EBTNodeResult::Succeeded;
}
