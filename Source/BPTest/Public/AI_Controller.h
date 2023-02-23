// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "AI_Controller.generated.h"

/**
 * 
 */
UCLASS()
class BPTEST_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAI_Controller();

	FVector GoalLocation;
	void FollowTarget();
	FHitResult OutHit;

	// Player Pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	APawn* PlayerPawn;
	// AI Navigation Data
	UNavigationSystemV1* NavSysystem;
	void RandomlySelectPatrolPoint();

	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	// AI perception component properties
	UFUNCTION()
		void OnSensesUpdate(AActor* SensedActor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, Category = "AI Sight")
	float SightRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "AI Sight")
	float SightFOV = 45;

	UPROPERTY(EditAnywhere, Category = "AI Sight")
	float SightAge = 3;

	UPROPERTY(EditAnywhere, Category = "AI Sight")
	float SightLooseRadius = 1600;

	UPROPERTY(EditAnywhere, Category = "AI Sight")
	UAISenseConfig_Sight* SightConfig;


	// AI Blackboard Data
	UPROPERTY(EditAnywhere, Category = "AI Blackboard")
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditAnywhere, Category = "AI Blackboard")
	UBlackboardData* BlackboardData;


	// AI Behaviour Tree
	UPROPERTY(EditAnywhere, Category = "AI Behaviour Tree")
	UBehaviorTree* BehaviorTree;
};
