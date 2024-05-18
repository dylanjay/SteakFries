// All rights reserved


#include "RangedEnemyController.h"
#include "ActionScriptComponent.h"
#include "ActionScriptGeneratorComponent.h"

void ARangedEnemyController::MoveInRange()
{
  Super::MoveInRange();

  if (!TryFindTarget(TargetLocation))
  {
    return;
  }

  // find shortest path to target
  
  // move in line

  ActionScript->PlayScript(ActionScriptGenerator->GetScript());
}

void ARangedEnemyController::Attack()
{

}
