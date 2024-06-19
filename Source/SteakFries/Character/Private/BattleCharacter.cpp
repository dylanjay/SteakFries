// All rights reserved


#include "BattleCharacter.h"
#include "GridMovementComponent.h"
#include "ActionPointResourceComponent.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "BattleGameState.h"
#include "StageGridManagerComponent.h"

void ABattleCharacter::Initialize(ETeam InTeam)
{
	Team = InTeam;

	StageGrid = StageGrid = GetWorld()->
		GetGameState<ABattleGameState>()->
		GetComponentByClass<UStageGridManagerComponent>()->
		GetStageGrid();

	GridMovementComp = GetComponentByClass<UGridMovementComponent>();

	ActionPointsComp = GetComponentByClass<UActionPointResourceComponent>();

	ActionScriptPlayerComp = GetComponentByClass<UActionScriptPlayerComponent>();

	ActionScriptGeneratorComp = GetComponentByClass<UActionScriptGeneratorComponent>();
	ActionScriptGeneratorComp->Initialize(ActionScriptPlayerComp, ActionPointsComp, GridMovementComp);
}
