// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller.h"
#include "Perception/AISenseConfig_Sight.h"

AAI_Controller::AAI_Controller()
{
	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	// Set Sight config
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = SightLooseRadius;
	SightConfig->PeripheralVisionAngleDegrees = SightFOV;
	SightConfig->SetMaxAge(SightAge);

	// Set affiliations
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	// set dominant sense
	GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	// on perception updated
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnSensesUpdate);
}

void AAI_Controller::BeginPlay()
{
	Super::BeginPlay();
	if (!BlackboardData)
		return;
	if (!BehaviorTree)
		return;
	
	UseBlackboard(BlackboardData, BlackboardComp);
	RunBehaviorTree(BehaviorTree);

	NavSysystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	RandomlySelectPatrolPoint();

	BlackboardComp->SetValueAsBool("Patrol", true);
}

void AAI_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(PlayerPawn)
	{
		GoalLocation = PlayerPawn->GetActorLocation();
		BlackboardComp->SetValueAsVector("TargetLocation", GoalLocation);
	}
}

void AAI_Controller::RandomlySelectPatrolPoint()
{
	if (NavSysystem)
	{
		FNavLocation RandomLocation;
		NavSysystem->GetRandomPointInNavigableRadius(GetPawn()->GetActorLocation(), 1000.0f, RandomLocation);
		GoalLocation = RandomLocation.Location;
		BlackboardComp->SetValueAsVector("TargetLocation", GoalLocation);
	}
}

void AAI_Controller::OnSensesUpdate(AActor* SensedActor, FAIStimulus Stimulus)
{
	APawn* TargetPlayer = nullptr;
	if (PlayerPawn == nullptr)
		TargetPlayer = Cast<APawn>(SensedActor);

	if (TargetPlayer && TargetPlayer->IsPlayerControlled())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			PlayerPawn = TargetPlayer;
			BlackboardComp->SetValueAsBool("Patrol", false);
		}
		else if(PlayerPawn && !LineOfSightTo(PlayerPawn))
		{
			PlayerPawn = nullptr;
			BlackboardComp->ClearValue("TargetLocation");
			BlackboardComp->SetValueAsBool("Patrol", true);
		}
	}
}
