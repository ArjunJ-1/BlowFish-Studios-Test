// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AI_Controller.h"
#include "BTTaskNode_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class BPTEST_API UBTTaskNode_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
