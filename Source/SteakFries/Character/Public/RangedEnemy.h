// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "RangedEnemy.generated.h"


UCLASS()
class STEAKFRIES_API ARangedEnemy : public AEnemy
{
	GENERATED_BODY()

public:

	virtual void SetIntention() override;

	virtual void ExecuteTurn() override;

	virtual void MoveInRange() override;

protected:

	UFUNCTION()
	void OnMoveInRangeComplete();

};
