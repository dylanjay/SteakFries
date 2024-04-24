// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovementComponent.h"
#include "StageGrid.h"
#include "StageCell.h"

UGridMovementComponent::UGridMovementComponent()
{

}

void UGridMovementComponent::Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell)
{
	StageGrid = InStageGrid;
	CurrentCell = InStageCell;
}

bool UGridMovementComponent::TryMoveToCell(AStageCell* ToCell)
{
	check(IsValid(ToCell));
	check(IsValid(CurrentCell));

	const TArray<int>& FromLocation = CurrentCell->GetGridLocation();
	const TArray<int>& ToLocation = ToCell->GetGridLocation();

	if (FromLocation == ToLocation)
	{
		return true;
	}

	// cannot move diagonally
	if (FromLocation[0] != ToLocation[0] && FromLocation[1] != ToLocation[1])
	{
		return false;
	}

	if (FromLocation[0] != ToLocation[0])
	{
		return TryMoveX(ToLocation[0] - FromLocation[0]);
	}
	else
	{
		return TryMoveY(ToLocation[1] - FromLocation[1]);
	}

	return false;
}

bool UGridMovementComponent::TryMoveX(int X)
{
	if (X == 0)
	{
		return false;
	}

	AStageCell* ToStageCell = StageGrid->TryMoveX(CurrentCell, X);
	if (CurrentCell == ToStageCell)
	{
		return false;
	}
	check(IsValid(ToStageCell));
	CurrentCell = ToStageCell;
	GetOwner()->SetActorLocation(CurrentCell->GetActorLocation() + LOCATION_OFFSET);
	return true;
}

bool UGridMovementComponent::TryMoveY(int Y)
{
	if (Y == 0)
	{
		return false;
	}

	AStageCell* ToStageCell = StageGrid->TryMoveY(CurrentCell, Y);
	if (CurrentCell == ToStageCell)
	{
		return false;
	}
	check(IsValid(ToStageCell));
	CurrentCell = ToStageCell;
	GetOwner()->SetActorLocation(CurrentCell->GetActorLocation() + LOCATION_OFFSET);
	return true;
}

void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

