// All rights reserved


#include "MoveAction.h"
#include "StageCell.h"

void UMoveAction::FillEdgeData(AStageCell* InFrom, AStageCell* InTo)
{
  check(IsValid(InFrom));
  check(IsValid(InTo));

  From = InFrom;
  To = InTo;
}
