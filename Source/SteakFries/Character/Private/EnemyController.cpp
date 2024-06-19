// All rights reserved


#include "EnemyController.h"
#include "Enemy.h"


void AEnemyController::Initialize()
{
  Enemy = Cast<AEnemy>(GetPawn());
  check(IsValid(Enemy));
}

void AEnemyController::SetIntention()
{
  Enemy->TrySetState(EEnemyState::SettingIntention);
}

void AEnemyController::ExecuteTurn()
{
}

void AEnemyController::MoveInRange()
{
}
