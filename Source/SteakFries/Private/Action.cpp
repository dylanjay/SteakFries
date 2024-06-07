// All rights reserved

#include "Action.h"
#include "StageCell.h"


void AAction::Initialize_Implementation(AStageGrid* InStageGrid, AStageCell* InCellLocation)
{
  StageGrid = InStageGrid;
  CellLocation = InCellLocation;
}

bool AAction::CanPlay(AStageCell* CurrentCell)
{
  return true;
}

void AAction::Play_Implementation(APawn* Pawn)
{
  PlayInternal(Pawn);
}

void AAction::PlayInternal(APawn* Pawn)
{
}
