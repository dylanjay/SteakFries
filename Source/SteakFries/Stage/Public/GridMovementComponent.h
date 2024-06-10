// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridTypes.h"
#include "StageCell.h"
#include "GridMovementComponent.generated.h"

class AStageGrid;


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	protected:

	AStageGrid* StageGrid = nullptr;

	AStageCell* CurrentCell = nullptr;

	const FVector LOCATION_OFFSET = FVector(0.0f, 0.0f, 5.0f);

public:

	void Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell);

	AStageCell* GetCurrentCell() const { return CurrentCell; }

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveTo(AStageCell* Destination);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveX(int32 X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveY(int32 Y);

protected:
	virtual void BeginPlay() override;

};
