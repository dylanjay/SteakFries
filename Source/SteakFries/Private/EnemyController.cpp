// All rights reserved


#include "EnemyController.h"
#include "BattleGameMode.h"
#include "TurnManager.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"
#include "Enemy.h"


void AEnemyController::Initialize(AStageGrid* InStageGrid)
{
  check(IsValid(InStageGrid));

  StageGrid = InStageGrid;

  Enemy = Cast<AEnemy>(GetPawn());
  check(IsValid(Enemy));

  TurnManager = Cast<ABattleGameMode>(Enemy->GetWorld()->GetAuthGameMode())->GetTurnManager();
  check(IsValid(TurnManager));

  ActionScriptGenerator = Enemy->GetComponentByClass<UActionScriptGeneratorComponent>();
  check(IsValid(ActionScriptGenerator));

  ActionScriptPlayer = Enemy->GetComponentByClass<UActionScriptPlayerComponent>();
  check(IsValid(ActionScriptPlayer));

  ActionScriptPlayer->OnScriptComplete.AddUniqueDynamic(this, &AEnemyController::OnMoveInRangeComplete);

  GridMovementComp = Enemy->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));
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

void AEnemyController::OnMoveInRangeComplete()
{
  SetIntention();
  TurnManager->EndTurn();
}

bool AEnemyController::TryFindTarget(UE::Math::TIntPoint<int32>& OutTargetLocation)
{
  ABattleGameMode* BattleGameMode = Cast<ABattleGameMode>(GetPawn()->GetWorld()->GetAuthGameMode());

  APawn* PlayerPawn = BattleGameMode->GetPlayerPawn();

  UGridMovementComponent* PlayerMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();

  OutTargetLocation = PlayerMovementComp->GetCurrentCell()->GetPoint();

  return true;
}
