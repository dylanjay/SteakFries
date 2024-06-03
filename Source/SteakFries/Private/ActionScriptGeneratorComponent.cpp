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
	if (OnReset.IsBound())
	{
		OnReset.Broadcast();
	}

	check(IsValid(ActionPoints));
	ActionPoints->Reset();

	check(IsValid(GridMovement));
	CurrentCell = GridMovement->GetCurrentCell();

	Script.Empty();
}

bool UActionScriptGeneratorComponent::TryAddAction(AAction* Action)
{
	check(IsValid(Action));
	check(IsValid(ActionPoints));

	if (!ActionPoints->CanAfford(Action->Cost))
	{
		return false;
	}

	Action->Initialize(StageGrid, CurrentCell);

	if (Action->IsA(AMoveAction::StaticClass()))
	{
		AMoveAction* MoveAction = Cast<AMoveAction>(Action);

		AStageCell* From = CurrentCell;

		UE::Math::TIntPoint<int> CurrentLocation = From->GetGridPoint();

		if (MoveAction->X != 0)
		{
			if (!StageGrid->CanMoveX(CurrentCell, MoveAction->X))
			{
				return false;
			}
			CurrentLocation.X += MoveAction->X;
		}
		else if (MoveAction->Y != 0)
		{
			if (!StageGrid->CanMoveY(CurrentCell, MoveAction->Y))
			{
				return false;
			}
			CurrentLocation.Y += MoveAction->Y;
		}

		AStageCell* To = StageGrid->GetCell(CurrentLocation);

		if (From == To)
		{
			return false;
		}

		MoveAction->FillEdgeData(To);

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

	AAction* ActionToRemove = Script.Last(0);

	check(IsValid(ActionToRemove));
	check(IsValid(ActionPoints));

	ActionPoints->Refund(ActionToRemove->Cost);

	return true;
}

