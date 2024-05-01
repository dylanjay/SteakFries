// All rights reserved


#include "MoveAction.h"
#include "StageCell.h"

void AMoveAction::FillEdgeData(AStageCell* InToCell)
{
  check(IsValid(InToCell));

  ToCell = InToCell;
}
