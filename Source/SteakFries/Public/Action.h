// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionComplete);

class AStageCell;
class AStageGrid;


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API AAction : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnActionComplete OnActionCompleteDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	float Cost = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float Delay = 0.5f;

	UPROPERTY()
	AStageGrid* StageGrid = nullptr;

	UPROPERTY()
	AStageCell* CellLocation = nullptr;

public:

	UFUNCTION(BlueprintNativeEvent)
	void Initialize(AStageGrid* InStageGrid, AStageCell* InCellLocation);

	UFUNCTION(BlueprintCallable)
	virtual bool CanPlay(AStageCell* CurrentCell);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Play(APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	float GetCost() const { return Cost; }

	UFUNCTION(BlueprintCallable)
	float GetDelay() const { return Delay; }

	UFUNCTION(BlueprintCallable)
	AStageCell* GetCellLocation() const { return CellLocation; }

protected:

	virtual void PlayInternal(APawn* Pawn);

};
