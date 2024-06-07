// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovementComponent.h"
#include "StageGrid.h"

void UGridMovementComponent::Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell)
{
	StageGrid = InStageGrid;
	CurrentCell = InStageCell;
}

bool UGridMovementComponent::TryMoveTo(AStageCell* Destination)
{
	check(IsValid(Destination));

	if (CurrentCell == Destination)
	{
		return false;
	}

	CurrentCell->Empty();
	
	CurrentCell = Destination;

	CurrentCell->Fill(GetOwner());

	GetOwner()->SetActorLocation(CurrentCell->GetActorLocation() + LOCATION_OFFSET);

	return true;
}

bool UGridMovementComponent::TryMoveX(int X)
{
	if (X == 0)
	{
		return false;
	}

	AStageCell* Destination = StageGrid->TryMoveX(CurrentCell, X);

	return TryMoveTo(Destination);
}

bool UGridMovementComponent::TryMoveY(int Y)
{
	if (Y == 0)
	{
		return false;
	}

	AStageCell* Destination = StageGrid->TryMoveY(CurrentCell, Y);
	
	return TryMoveTo(Destination);
}

void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}
