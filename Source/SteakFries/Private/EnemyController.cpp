// All rights reserved


#include "EnemyController.h"
#include "BattleGameMode.h"
#include "TurnManager.h"
#include "ActionScriptComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"


void AEnemyController::Initialize()
{
  APawn* EnemyPawn = GetPawn();

  check(IsValid(EnemyPawn));

  TurnManager = Cast<ABattleGameMode>(EnemyPawn->GetWorld()->GetAuthGameMode())->GetTurnManager();
  check(IsValid(TurnManager));

  ActionScriptGenerator = EnemyPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
  check(IsValid(ActionScriptGenerator));

  ActionScript = EnemyPawn->GetComponentByClass<UActionScriptComponent>();
  check(IsValid(ActionScript));

  ActionScript->OnScriptComplete.AddUniqueDynamic(this, &AEnemyController::OnMoveInRangeComplete);
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

bool AEnemyController::TryFindTarget(TArray<int>& OutTargetLocation)
{
  ABattleGameMode* BattleGameMode = Cast<ABattleGameMode>(GetPawn()->GetWorld()->GetAuthGameMode());

  APawn* PlayerPawn = BattleGameMode->GetPlayerPawn();

  UGridMovementComponent* PlayerMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();

  OutTargetLocation = PlayerMovementComp->GetCurrentCell()->GetGridLocation();

  return true;
}
