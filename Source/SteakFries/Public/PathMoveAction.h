// All rights reserved

#pragma once

#include "MoveAction.h"
#include "PathMoveAction.generated.h"

UCLASS()
class STEAKFRIES_API APathMoveAction : public AMoveAction
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UGridMovementComponent* GridMovementComp = nullptr;

	UPROPERTY()
	TArray<AStageCell*> Path;

	// Start move to the "1st" node in path
	int PathIndex = 1;

	FTimerHandle DelayTimerHandle;

protected:

	UFUNCTION()
	void OnDelayElapsed();

public:

	virtual bool CanPlay(AStageCell* CurrentCell) override;

	virtual void PlayInternal(APawn* Pawn);

	void SetDestination(AStageCell* InDestination);

	TArray<AStageCell*> GetPath() const { return Path; }

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
