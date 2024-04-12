// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovement.generated.h"

// Forward Declarations
class AStageGrid;
class AStageCell;


UCLASS( BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UGridMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGridMovement();

	void Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveX(int X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveY(int Y);

protected:

	AStageGrid* StageGrid;

	AStageCell* StageCell;

protected:
	virtual void BeginPlay() override;		

};
