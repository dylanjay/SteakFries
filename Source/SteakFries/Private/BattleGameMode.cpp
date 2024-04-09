// All rights reserved


#include "BattleGameMode.h"
#include "CharacterSpawner.h"
#include "StageGrid.h"

APawn* ABattleGameMode::GetPlayerPawn() const
{
  return PlayerPawn;
}

void ABattleGameMode::BeginPlay()
{
  CharacterSpawner = GetWorld()->SpawnActor<ACharacterSpawner>(CharacterSpawnerClass);

  StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);

  StageGrid->Initialize(CharacterSpawner);

  PlayerPawn = CharacterSpawner->SpawnPlayerPawn();

  Super::BeginPlay();
}
