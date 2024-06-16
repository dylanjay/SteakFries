// All rights reserved

#include "Enemy.h"
#include "StageGrid.h"

bool AEnemy::TrySetState(EEnemyState NewState)
{
  if (State == NewState)
  {
    return false;
  }

  OnEnemyStateExitDelegate.Broadcast(State);

  State = NewState;

  switch (State)
  {
  case EEnemyState::SettingIntention:
    MoveInRange();
    break;
  case EEnemyState::ExecutingTurn:
    ExecuteTurn();
    break;
  }

  check(State == NewState);

  OnEnemyStateEnterDelegate.Broadcast(State);
  
  return true;
}

void AEnemy::Initialize()
{
  // TODO: Prepare
  TrySetState(EEnemyState::Default);
}

void AEnemy::SetIntention()
{
  TrySetState(EEnemyState::IntentionSet);
}

void AEnemy::ExecuteTurn()
{
}

void AEnemy::MoveInRange()
{
  // TODO: Teleport in range

  SetIntention();
}

void AEnemy::TryFindTarget()
{

}
