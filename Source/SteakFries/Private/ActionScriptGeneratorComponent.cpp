// All rights reserved

#include "ActionScriptGeneratorComponent.h"
#include "ActionPointResourceComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"
#include "MoveAction.h"
#include "StageGrid.h"


void UActionScriptGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UActionScriptGeneratorComponent::Initialize(UActionPointResourceComponent* InActionPoints, UGridMovementComponent* InGridMovement, AStageGrid* InStageGrid)
{
	check(IsValid(InActionPoints));

	ActionPoints = InActionPoints;
	GridMovement = InGridMovement;
	StageGrid = InStageGrid;
	CurrentCell = GridMovement->GetCurrentCell();
	check(IsValid(CurrentCell));
}

void UActionScriptGeneratorComponent::Reset()
{
	check(IsValid(ActionPoints));
	ActionPoints->Reset();

	check(IsValid(GridMovement));
	CurrentCell = GridMovement->GetCurrentCell();

	Script.Empty();
}

bool UActionScriptGeneratorComponent::TryAddAction(UAction* Action)
{
	check(IsValid(Action));
	check(IsValid(ActionPoints));

	if (!ActionPoints->CanAfford(Action->Cost))
	{
		return false;
	}

	if (Action->IsA(UMoveAction::StaticClass()))
	{
		UMoveAction* MoveAction = Cast<UMoveAction>(Action);

		AStageCell* From = CurrentCell;

		TArray<int> CurrentLocation = From->GetGridLocation();

		if (MoveAction->X != 0)
		{
			CurrentLocation[0] += MoveAction->X;
		}
		else if (MoveAction->Y != 0)
		{
			CurrentLocation[1] += MoveAction->Y;
		}

		if (!StageGrid->IsValidLocation(CurrentLocation))
		{
			return false;
		}

		AStageCell* To = StageGrid->GetCell(CurrentLocation);

		if (From == To)
		{
			return false;
		}

		MoveAction->FillEdgeData(From, To);

		CurrentCell = To;
	}

	Script.Add(Action);

	ActionPoints->TryConsume(Action->Cost);
	
	if (OnActionAdded.IsBound())
	{
		OnActionAdded.Broadcast(Action);
	}

	return true;
}

bool UActionScriptGeneratorComponent::TryRemoveEnd()
{
	if (Script.IsEmpty())
	{
		return false;
	}

	UAction* ActionToRemove = Script.Last(0);

	check(IsValid(ActionToRemove));
	check(IsValid(ActionPoints));

	ActionPoints->Refund(ActionToRemove->Cost);

	return true;
}

