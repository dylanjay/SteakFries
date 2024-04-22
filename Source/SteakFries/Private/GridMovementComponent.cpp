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
	GetOwner()->SetActorLocation(CurrentCell->GetActorLocation());
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
	GetOwner()->SetActorLocation(CurrentCell->GetActorLocation());
	return true;
}

void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

