// All rights reserved


#include "RangedEnemy.h"

void ARangedEnemy::Initialize()
{
}

void ARangedEnemy::SetIntention()
{
}

void ARangedEnemy::ExecuteTurn()
{
}

void ARangedEnemy::MoveInRange()
{
  /*if (!TryFindTarget(TargetLocation))
  {
    return;
  }

  UE::Math::TIntPoint<int32> CurrentLocation = GridMovementComp->GetCurrentCell()->GetPoint();

  if (CurrentLocation.X != TargetLocation.X)
  {
    TPoint VantagePoint = TPoint(TargetLocation.X, CurrentLocation.Y);
    AStageCell* TargetCell = StageGrid->GetCell(VantagePoint);

    APathMoveAction* PathMove = GetWorld()->SpawnActor<APathMoveAction>(APathMoveAction::StaticClass());

    PathMove->SetDestination(TargetCell);

    if (!ActionScriptGenerator->TryAddAction(PathMove))
    {
      return;
    }
  }

  ActionScriptPlayer->PlayScript(ActionScriptGenerator->GetScript());*/
}
