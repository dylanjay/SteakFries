// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"
#include "StageGrid.h"
#include "StageCell.h"

UGridMovement::UGridMovement()
{

}

void UGridMovement::Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell)
{
	StageGrid = InStageGrid;
	StageCell = InStageCell;
}

bool UGridMovement::TryMoveX(int X)
{
	if (X == 0)
	{
		return false;
	}

	AStageCell* ToStageCell = StageGrid->TryMoveX(StageCell, X);
	if (StageCell == ToStageCell)
	{
		return false;
	}
	check(IsValid(ToStageCell));
	StageCell = ToStageCell;
	GetOwner()->SetActorLocation(StageCell->GetActorLocation());
	return true;
}

bool UGridMovement::TryMoveY(int Y)
{
	if (Y == 0)
	{
		return false;
	}

	AStageCell* ToStageCell = StageGrid->TryMoveY(StageCell, Y);
	if (StageCell == ToStageCell)
	{
		return false;
	}
	check(IsValid(ToStageCell));
	StageCell = ToStageCell;
	GetOwner()->SetActorLocation(StageCell->GetActorLocation());
	return true;
}

void UGridMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

