// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovementComponent.h"
#include "StageGrid.h"
#include "BattleGameState.h"
#include "StageGridManagerComponent.h"

void UGridMovementComponent::Initialize(AStageCell* InStageCell)
{
	CurrentCell = InStageCell;
	check(IsValid(CurrentCell));

	StageGrid = GetWorld()->GetGameState<ABattleGameState>()->GetStageGrid();
	check(IsValid(StageGrid));
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

bool UGridMovementComponent::TryMoveX(int32 X)
{
	if (X == 0)
	{
		return false;
	}

	AStageCell* Destination = StageGrid->TryMoveX(CurrentCell, X);

	return TryMoveTo(Destination);
}

bool UGridMovementComponent::TryMoveY(int32 Y)
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
