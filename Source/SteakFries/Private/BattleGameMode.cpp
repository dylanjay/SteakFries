// All rights reserved


#include "BattleGameMode.h"
#include "TurnManagerComponent.h"
#include "CharacterSpawnManagerComponent.h"
#include "CharacterTypes.h"
#include "BattleGameState.h"


void ABattleGameMode::BeginPlay()
{
	TurnManager = GetComponentByClass<UTurnManagerComponent>();
	check(IsValid(TurnManager));

	CharacterSpawnManager = GetComponentByClass<UCharacterSpawnManagerComponent>();
	check(IsValid(CharacterSpawnManager));

	ABattleGameState* BattleGameState = GetGameState<ABattleGameState>();

	BattleGameState->Initialize();

	const TPoint PlayerStartingPoint = TPoint(PlayerStartingPointArray[0], PlayerStartingPointArray[1]);
	CharacterSpawnManager->Spawn<APlayerBattleCharacter>(PlayerClass, ETeam::Player, PlayerStartingPoint);

	TPoint EnemyStartingPoint = TPoint(EnemyStartingPointArray[0], EnemyStartingPointArray[1]);
	CharacterSpawnManager->Spawn<AEnemy>(EnemyClass, ETeam::Enemy, EnemyStartingPoint);

	TurnManager->Initialize();

	StartPlay();

	Super::BeginPlay();
}
