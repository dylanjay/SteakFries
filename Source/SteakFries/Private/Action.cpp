// All rights reserved

#include "Action.h"
#include "StageCell.h"


void AAction::Initialize_Implementation(AStageGrid* InStageGrid, AStageCell* InCellLocation)
{
  StageGrid = InStageGrid;
  CellLocation = InCellLocation;
}

void AAction::DoAction_Implementation(APawn* Pawn)
{
}