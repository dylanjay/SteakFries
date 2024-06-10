// All rights reserved


#include "RangedEnemyController.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"
#include "StageGrid.h"
#include "PathMoveAction.h"


void ARangedEnemyController::MoveInRange()
{
  Super::MoveInRange();

  if (!TryFindTarget(TargetLocation))
  {
    return;
  }

  UE::Math::TIntPoint<int32> CurrentLocation = GridMovementComp->GetCurrentCell()->GetGridPoint();
  
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

  ActionScriptPlayer->PlayScript(ActionScriptGenerator->GetScript());
}

void ARangedEnemyController::Attack()
{

}
