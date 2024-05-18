// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "RangedEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class STEAKFRIES_API ARangedEnemyController : public AEnemyController
{
	GENERATED_BODY()

public:

	virtual void MoveInRange() override;

	virtual void Attack() override;
	
};
