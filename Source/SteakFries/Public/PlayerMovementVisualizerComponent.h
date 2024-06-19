// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerMovementVisualizerComponent.generated.h"

class APlayerControllerBase;
class AStageGrid;


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UPlayerMovementVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	APlayerControllerBase* PlayerController = nullptr;

	AStageGrid* StageGrid = nullptr;

	bool bIsActive = false;

public:

	void Initialize(APlayerControllerBase* InPlayerController, AStageGrid* InStageGrid);

protected:

	UFUNCTION()
	void OnPlayerControllerStateChange(EPlayerControllerState NewState);

	void ActivateVisual();

	void DeactivateVisual();

};
