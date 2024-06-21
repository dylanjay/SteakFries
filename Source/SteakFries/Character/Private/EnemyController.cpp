// All rights reserved


#include "EnemyController.h"
#include "Enemy.h"


void AEnemyController::Initialize(AEnemy* InEnemy)
{
  Enemy = InEnemy;
  check(IsValid(Enemy));

  Possess(Enemy);
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
