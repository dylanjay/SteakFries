// All rights reserved


#include "RangedEnemy.h"
#include "GridMovementComponent.h"
#include "PathMoveAction.h"
#include "StageGrid.h"
#include "ActionScriptGeneratorComponent.h"
#include "ActionScriptPlayerComponent.h"

void ARangedEnemy::Initialize()
{
}

void ARangedEnemy::SetIntention()
{


    TrySetState(EEnemyState::IntentionSet);
}

void ARangedEnemy::ExecuteTurn()
{
}

void ARangedEnemy::MoveInRange()
{
  if (!TryFindTarget())
  {
    return;
  }

  UE::Math::TIntPoint<int32> CurrentLocation = GridMovementComp->GetCurrentCell()->GetPoint();

  if (CurrentLocation.X != TargetPoint.X)
  {
    TPoint VantagePoint = TPoint(TargetPoint.X, CurrentLocation.Y);
    AStageCell* TargetCell = StageGrid->GetCell(VantagePoint);

    APathMoveAction* PathMove = GetWorld()->SpawnActor<APathMoveAction>(APathMoveAction::StaticClass());

    PathMove->SetDestination(TargetCell);

    if (!ActionScriptGeneratorComp->TryAddAction(PathMove))
    {
      return;
    }
  }

  ActionScriptPlayerComp->OnScriptComplete.AddUniqueDynamic(this, &ARangedEnemy::OnMoveInRangeComplete);

  ActionScriptPlayerComp->PlayScript(ActionScriptGeneratorComp->GetScript());
}

void ARangedEnemy::OnMoveInRangeComplete()
{
    ActionScriptPlayerComp->OnScriptComplete.RemoveDynamic(this, &ARangedEnemy::OnMoveInRangeComplete);

    SetIntention();
}
