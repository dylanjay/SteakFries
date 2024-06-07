// All rights reserved


#include "PathMoveAction.h"
#include "StageGrid.h"
#include "GridMovementComponent.h"


bool APathMoveAction::CanPlay(AStageCell* CurrentCell)
{
  check(IsValid(Destination));

  if (!StageGrid->TryFindPathToCell(CurrentCell, Destination, Path))
  {
    return false;
  }

  return true;
}

void APathMoveAction::OnDelayElapsed()
{
  if (!GridMovementComp->TryMoveTo(Path[PathIndex]))
  {
    return;
  }

  PathIndex++;

  if (PathIndex < Path.Num())
  {
    GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &APathMoveAction::OnDelayElapsed, Delay, false);
  }
  else
  {
    if (OnActionCompleteDelegate.IsBound())
    {
      OnActionCompleteDelegate.Broadcast();
    }
  }
}


void APathMoveAction::PlayInternal(APawn* Pawn)
{
  GridMovementComp = Pawn->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));

  if (!GridMovementComp->TryMoveTo(Path[PathIndex]))
  {
    return;
  }

  PathIndex++;

  GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &APathMoveAction::OnDelayElapsed, Delay, false);
}

void APathMoveAction::SetDestination(AStageCell* InDestination)
{
  check(IsValid(InDestination));

  Destination = InDestination;
}

void APathMoveAction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  Super::EndPlay(EndPlayReason);

  GetWorld()->GetTimerManager().ClearTimer(DelayTimerHandle);
}
