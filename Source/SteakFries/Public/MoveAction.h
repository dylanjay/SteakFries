// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "MoveAction.generated.h"

class AStageCell;


UCLASS()
class STEAKFRIES_API AMoveAction : public AAction
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int X;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int Y;

	UPROPERTY()
	AStageCell* From;

	UPROPERTY()
	AStageCell* To;

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void FillEdgeData(AStageCell* InFrom, AStageCell* InTo);
	
};
