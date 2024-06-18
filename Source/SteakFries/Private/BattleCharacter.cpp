// All rights reserved


#include "BattleCharacter.h"
#include "GridMovementComponent.h"
#include "ActionPointResourceComponent.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "BattleGameMode.h"

void ABattleCharacter::Initialize()
{
	StageGrid = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode())->GetStageGrid();

	GridMovementComp = GetComponentByClass<UGridMovementComponent>();

	ActionPointsComp = GetComponentByClass<UActionPointResourceComponent>();

	ActionScriptPlayerComp = GetComponentByClass<UActionScriptPlayerComponent>();

	ActionScriptGeneratorComp = GetComponentByClass<UActionScriptGeneratorComponent>();
	ActionScriptGeneratorComp->Initialize(ActionScriptPlayerComp, ActionPointsComp, GridMovementComp);
}
