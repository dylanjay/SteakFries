// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class APawn;
class ATurnManager;
class UActionScriptGeneratorComponent;
class UActionScriptComponent;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class STEAKFRIES_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void Initialize();

	virtual void SetAttackIntention();

	virtual void Attack();

	virtual void MoveInRange();

protected:

	UFUNCTION()
	void OnMoveInRangeComplete();

	bool TryFindTarget(TArray<int> &OutTargetLocation);

protected:

	ATurnManager* TurnManager = nullptr;

	UActionScriptGeneratorComponent* ActionScriptGenerator = nullptr;

	UActionScriptComponent* ActionScript = nullptr;
};
