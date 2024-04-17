// All rights reserved


#include "BattleGameMode.h"
#include "CharacterSpawner.h"
#include "StageGrid.h"

ACharacterSpawner* ABattleGameMode::GetCharacterSpawner() const
{
  return CharacterSpawner;
}

AStageGrid* ABattleGameMode::GetStageGrid() const
{
  return StageGrid;
}

APawn* ABattleGameMode::GetPlayerPawn() const
{
  return PlayerPawn;
}

void ABattleGameMode::BeginPlay()
{
  CharacterSpawner = GetWorld()->SpawnActor<ACharacterSpawner>(CharacterSpawnerClass);

  StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);

  StageGrid->Initialize(CharacterSpawner);

  PlayerPawn = CharacterSpawner->SpawnCharacterPawn(PlayerPawnClass, StartingPlayerLocation);

  if (IsValid(EnemyPawnClass))
  {
    CharacterSpawner->SpawnCharacterPawn(EnemyPawnClass, StartingEnemyLocation);
  }

  Super::BeginPlay();
}
