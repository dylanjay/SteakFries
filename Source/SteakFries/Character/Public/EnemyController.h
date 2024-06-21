// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class STEAKFRIES_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	AEnemy* Enemy = nullptr;

public:

	virtual void Initialize(AEnemy* InEnemy);

	virtual void SetIntention();

	virtual void ExecuteTurn();

	virtual void MoveInRange();

	AEnemy* GetEnemy() const { return Enemy; }
};
