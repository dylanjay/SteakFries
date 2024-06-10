// All rights reserved

#pragma once

#include "Action.h"
#include "MoveAction.generated.h"


UCLASS()
class STEAKFRIES_API AMoveAction : public AAction
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	AStageCell* Destination = nullptr;

public:

	AStageCell* GetDestination() const { return Destination; }
};
