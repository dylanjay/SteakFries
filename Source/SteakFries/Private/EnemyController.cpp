// All rights reserved


#include "EnemyController.h"
#include "BattleGameMode.h"
#include "TurnManager.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"


void AEnemyController::Initialize(AStageGrid* InStageGrid)
{
  check(IsValid(InStageGrid));

  StageGrid = InStageGrid;

  EnemyPawn = GetPawn();

  check(IsValid(EnemyPawn));

  TurnManager = Cast<ABattleGameMode>(EnemyPawn->GetWorld()->GetAuthGameMode())->GetTurnManager();
  check(IsValid(TurnManager));

  ActionScriptGenerator = EnemyPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
  check(IsValid(ActionScriptGenerator));

  ActionScriptPlayer = EnemyPawn->GetComponentByClass<UActionScriptPlayerComponent>();
  check(IsValid(ActionScriptPlayer));

  ActionScriptPlayer->OnScriptComplete.AddUniqueDynamic(this, &AEnemyController::OnMoveInRangeComplete);

  GridMovementComp = EnemyPawn->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));
}

void AEnemyController::SetAttackIntention()
{
}

void AEnemyController::Attack()
{
}

void AEnemyController::MoveInRange()
{
}

void AEnemyController::OnMoveInRangeComplete()
{
  SetAttackIntention();
  TurnManager->EndTurn();
}

bool AEnemyController::TryFindTarget(UE::Math::TIntPoint<int>& OutTargetLocation)
{
  ABattleGameMode* BattleGameMode = Cast<ABattleGameMode>(GetPawn()->GetWorld()->GetAuthGameMode());

  APawn* PlayerPawn = BattleGameMode->GetPlayerPawn();

  UGridMovementComponent* PlayerMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();

  OutTargetLocation = PlayerMovementComp->GetCurrentCell()->GetGridPoint();

  return true;
}
