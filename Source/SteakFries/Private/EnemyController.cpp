// All rights reserved


#include "EnemyController.h"
#include "BattleGameMode.h"
#include "TurnManager.h"
#include "ActionScriptComponent.h"
#include "AIActionScriptGeneratorComponent.h"

void AEnemyController::SetPawn(APawn* InPawn)
{
  check(IsValid(InPawn));

  Super::SetPawn(InPawn);

  TurnManager = Cast<ABattleGameMode>(InPawn->GetWorld()->GetAuthGameMode())->GetTurnManager();
  check(IsValid(TurnManager));

  ActionScriptGenerator = InPawn->GetComponentByClass<UAIActionScriptGeneratorComponent>();
  check(IsValid(ActionScriptGenerator));

  ActionScript = InPawn->GetComponentByClass<UActionScriptComponent>();
  check(IsValid(ActionScript));

  ActionScript->OnScriptComplete.AddUniqueDynamic(this, &AEnemyController::OnScriptComplete);
}

void AEnemyController::TakeTurn()
{
  ActionScriptGenerator->GenerateMoveToTargetAndAttackScript();

  ActionScript->PlayScript(ActionScriptGenerator->GetScript());
}

void AEnemyController::OnScriptComplete()
{
  TurnManager->EndTurn();
}
