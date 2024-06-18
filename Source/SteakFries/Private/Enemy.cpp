// All rights reserved

#include "Enemy.h"
#include "StageGrid.h"
#include "BattleGameState.h"
#include "PlayerBattleCharacter.h"
#include "GridMovementComponent.h"

bool AEnemy::TrySetState(EEnemyState NewState)
{
  if (State == NewState)
  {
    return false;
  }

  OnStateExitDelegate.Broadcast(this, State);

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

  OnStateEnterDelegate.Broadcast(this, State);
  
  return true;
}

void AEnemy::Initialize()
{
    Super::Initialize();

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

bool AEnemy::TryFindTarget()
{
    ABattleGameState* BattleGameState = GetWorld()->GetAuthGameMode()->GetGameState<ABattleGameState>();

    APlayerBattleCharacter* PlayerCharacter = BattleGameState->GetPlayerCharacters()[0];

    UGridMovementComponent* PlayerMovementComp = PlayerCharacter->GetComponentByClass<UGridMovementComponent>();

    TargetPoint = PlayerMovementComp->GetCurrentCell()->GetPoint();

    return true;
}
