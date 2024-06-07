// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "RangedEnemyController.generated.h"

#define TPoint UE::Math::TIntPoint<int>


UCLASS()
class STEAKFRIES_API ARangedEnemyController : public AEnemyController
{
	GENERATED_BODY()

public:

	virtual void MoveInRange() override;

	virtual void Attack() override;
	
};
