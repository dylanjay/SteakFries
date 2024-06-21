// All rights reserved

#include "BattleGameState.h"
#include "CharacterManagerComponent.h"


void ABattleGameState::Initialize()
{
	StageGridManager = GetComponentByClass<UStageGridManagerComponent>();
	check(IsValid(StageGridManager));

	StageGridManager->SpawnStageGrid();

	CharacterManager = GetComponentByClass<UCharacterManagerComponent>();
	check(IsValid(CharacterManager));

	CharacterManager->Initialize();
}