// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "MoveAction.h"
#include "SingleMoveAction.generated.h"

class AStageCell;


UCLASS()
class STEAKFRIES_API ASingleMoveAction : public AMoveAction
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 X;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 Y;

public:

	virtual bool CanPlay(AStageCell* CurrentCell) override;
};
