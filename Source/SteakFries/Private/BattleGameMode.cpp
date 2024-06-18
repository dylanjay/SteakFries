// All rights reserved


#include "BattleGameMode.h"
#include "TurnManager.h"
#include "CharacterSpawner.h"
#include "StageGrid.h"
#include "StageCell.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BattleCharacter.h"
#include "BattleGameState.h"
#include "PlayerBattleCharacter.h"


ABattleGameMode::~ABattleGameMode()
{
  delete PlayerStartingPoint;
  delete EnemyStartingPoint;
}

void ABattleGameMode::BeginPlay()
{
    TArray<ABattleCharacter*> AllCharacters;
    TArray<APlayerBattleCharacter*> PlayerCharacters;
    TArray<AEnemy*> Enemies;

  TurnManager = GetWorld()->SpawnActor<ATurnManager>(TurnManagerClass);

  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

  CharacterSpawner = GetWorld()->SpawnActor<ACharacterSpawner>(CharacterSpawnerClass);
  check(IsValid(CharacterSpawner));

  StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);
  check(IsValid(StageGrid));
  
  const FVector PlayerSpawnLocation = StageGrid->GetCell(PlayerStartingPointArray)->GetActorLocation();
  APlayerBattleCharacter* PlayerCharacter = CharacterSpawner->Spawn<APlayerBattleCharacter>(PlayerClass, PlayerSpawnLocation);
  check(IsValid(PlayerCharacter));

  AllCharacters.Add(PlayerCharacter);
  PlayerCharacters.Add(PlayerCharacter);

  PlayerStartingPoint = new UE::Math::TIntPoint<int32>(PlayerStartingPointArray[0], PlayerStartingPointArray[1]);
  StageGrid->InitializeOnGrid(PlayerCharacter, *PlayerStartingPoint);

  PlayerCharacter->Initialize();

  if (IsValid(EnemyClass))
  {
    const FVector EnemySpawnLocation = StageGrid->GetCell(EnemyStartingPointArray)->GetActorLocation();
    AEnemy* Enemy = CharacterSpawner->Spawn<AEnemy>(EnemyClass, EnemySpawnLocation);
    check(IsValid(Enemy));

    AEnemyController* EnemyController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
    check(IsValid(EnemyController));

    EnemyController->Possess(Enemy);
    EnemyController->Initialize();
    
    AllCharacters.Add(Enemy);
    Enemies.Add(Enemy);

    EnemyStartingPoint = new UE::Math::TIntPoint<int32>(EnemyStartingPointArray[0], EnemyStartingPointArray[1]);
    StageGrid->InitializeOnGrid(Enemy, *EnemyStartingPoint);

    Enemy->Initialize();
  }
  
  TurnManager->Initialize(AllCharacters);

  ABattleGameState* BattleGameState = GetGameState<ABattleGameState>();
  BattleGameState->SetAllCharacters(AllCharacters);
  BattleGameState->SetPlayerCharacters(PlayerCharacters);
  BattleGameState->SetEnemies(Enemies);

  TurnManager->Start();

  Super::BeginPlay();
}
