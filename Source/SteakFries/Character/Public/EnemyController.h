// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class APawn;
class AEnemy;
class UTurnManagerComponent;
class UActionScriptGeneratorComponent;
class UActionScriptPlayerComponent;
class AStageGrid;
class UGridMovementComponent;

UCLASS(Abstract, Blueprintable)
class STEAKFRIES_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	AEnemy* Enemy = nullptr;

public:

	virtual void Initialize();

	virtual void SetIntention();

	virtual void ExecuteTurn();

	virtual void MoveInRange();

	AEnemy* GetEnemy() const { return Enemy; }
};
