// All rights reserved

#include "Action.h"
#include "StageCell.h"
#include "BattleGameState.h"


void AAction::Initialize(AStageCell* InCellLocation)
{
  CellLocation = InCellLocation;
  check(IsValid(CellLocation));

  StageGrid = GetWorld()->GetGameState<ABattleGameState>()->GetStageGrid();
  check(IsValid(StageGrid));
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
