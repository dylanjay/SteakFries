// All rights reserved

#include "SingleMoveAction.h"
#include "StageCell.h"
#include "StageGrid.h"

bool ASingleMoveAction::CanPlay(AStageCell* CurrentCell)
{
	AStageCell* Start = CurrentCell;

	UE::Math::TIntPoint<int32> CurrentLocation = Start->GetPoint();

	if (X != 0)
	{
		if (!StageGrid->CanMoveX(CurrentCell, X))
		{
			return false;
		}
		CurrentLocation.X += X;
	}
	else if (Y != 0)
	{
		if (!StageGrid->CanMoveY(CurrentCell, Y))
		{
			return false;
		}
		CurrentLocation.Y += Y;
	}

	Destination = StageGrid->GetCell(CurrentLocation);

	return Start != Destination;
}