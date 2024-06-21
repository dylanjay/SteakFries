// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageGridManagerComponent.generated.h"

class AStageGrid;


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class STEAKFRIES_API UStageGridManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageGrid> StageGridClass;

	UPROPERTY()
	AStageGrid* StageGrid = nullptr;

public:

	void SpawnStageGrid();

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const { return StageGrid; }

};
