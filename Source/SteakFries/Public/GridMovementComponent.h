// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementComponent.generated.h"

// Forward Declarations
class AStageGrid;
class AStageCell;


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGridMovementComponent();

	void Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell);

	AStageCell* GetCurrentCell() const { return CurrentCell; }

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveX(int X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveY(int Y);

protected:

	AStageGrid* StageGrid = nullptr;

	AStageCell* CurrentCell = nullptr;

protected:
	virtual void BeginPlay() override;		

};
