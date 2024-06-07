// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class APawn;
class ATurnManager;
class UActionScriptGeneratorComponent;
class UActionScriptPlayerComponent;
class AStageGrid;
class UGridMovementComponent;

UCLASS(Abstract, Blueprintable)
class STEAKFRIES_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	APawn* EnemyPawn = nullptr;

	UE::Math::TIntPoint<int> TargetLocation;

	ATurnManager* TurnManager = nullptr;

	UActionScriptGeneratorComponent* ActionScriptGenerator = nullptr;

	UActionScriptPlayerComponent* ActionScriptPlayer = nullptr;

	AStageGrid* StageGrid = nullptr;

	UGridMovementComponent* GridMovementComp = nullptr;

public:

	virtual void Initialize(AStageGrid* InStageGrid);

	virtual void SetAttackIntention();

	virtual void Attack();

	virtual void MoveInRange();

protected:

	UFUNCTION()
	void OnMoveInRangeComplete();

	bool TryFindTarget(UE::Math::TIntPoint<int>&OutTargetLocation);
};
