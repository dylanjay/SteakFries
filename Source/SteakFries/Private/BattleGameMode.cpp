// All rights reserved


#include "BattleGameMode.h"
#include "TurnManager.h"
#include "CharacterSpawner.h"
#include "StageGrid.h"
#include "StageCell.h"
#include "GridMovementVisualizerComponent.h"
#include "GridMovementComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "ActionPointResourceComponent.h"
#include "SwordAttackVisualizerComponent.h"
#include "EnemyController.h"
#include "Enemy.h"

ACharacterSpawner* ABattleGameMode::GetCharacterSpawner() const
{
  return CharacterSpawner;
}

AStageGrid* ABattleGameMode::GetStageGrid() const
{
  return StageGrid;
}

ATurnManager* ABattleGameMode::GetTurnManager() const
{
  return TurnManager;
}

APawn* ABattleGameMode::GetPlayerPawn() const
{
  return PlayerPawn;
}

ABattleGameMode::~ABattleGameMode()
{
  delete PlayerStartingPoint;
  delete EnemyStartingPoint;
}

void ABattleGameMode::BeginPlay()
{
  TurnManager = GetWorld()->SpawnActor<ATurnManager>(TurnManagerClass);

  TArray<APawn*> Pawns;

  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

  CharacterSpawner = GetWorld()->SpawnActor<ACharacterSpawner>(CharacterSpawnerClass);
  check(IsValid(CharacterSpawner));

  StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);
  check(IsValid(StageGrid));
  
  const FVector PlayerSpawnLocation = StageGrid->GetCell(PlayerStartingPointArray)->GetActorLocation();
  PlayerPawn = CharacterSpawner->SpawnCharacterPawn(PlayerPawnClass, PlayerSpawnLocation);
  check(IsValid(PlayerPawn));

  PlayerController->Possess(PlayerPawn);

  Pawns.Add(PlayerPawn);

  PlayerStartingPoint = new UE::Math::TIntPoint<int32>(PlayerStartingPointArray[0], PlayerStartingPointArray[1]);
  StageGrid->InitializeOnGrid(PlayerPawn, *PlayerStartingPoint);

  UGridMovementComponent* GridMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));

  UActionPointResourceComponent* ActionPointResourceComp = PlayerPawn->GetComponentByClass<UActionPointResourceComponent>();

  UActionScriptPlayerComponent* ActionScriptPlayerComp = PlayerPawn->GetComponentByClass<UActionScriptPlayerComponent>();

  UActionScriptGeneratorComponent* ActionScriptGeneratorComp = PlayerPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
  ActionScriptGeneratorComp->Initialize(ActionScriptPlayerComp, ActionPointResourceComp, GridMovementComp, StageGrid);

  if (IsValid(EnemyPawnClass))
  {
    const FVector EnemySpawnLocation = StageGrid->GetCell(EnemyStartingPointArray)->GetActorLocation();
    AEnemy* Enemy = Cast<AEnemy>(CharacterSpawner->SpawnCharacterPawn(EnemyPawnClass, EnemySpawnLocation));
    check(IsValid(Enemy));

    AEnemyController* EnemyController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
    check(IsValid(EnemyController));

    EnemyController->Possess(Enemy);
    EnemyController->Initialize(StageGrid);

    Pawns.Add(Enemy);

    EnemyStartingPoint = new UE::Math::TIntPoint<int32>(EnemyStartingPointArray[0], EnemyStartingPointArray[1]);
    StageGrid->InitializeOnGrid(Enemy, *EnemyStartingPoint);

    UGridMovementComponent* EnemyGridMovementComp = Enemy->GetComponentByClass<UGridMovementComponent>();
    check(IsValid(EnemyGridMovementComp));

    UActionPointResourceComponent* EnemyActionPointResourceComp = Enemy->GetComponentByClass<UActionPointResourceComponent>();

    UActionScriptPlayerComponent* EnemyActionScriptPlayerComp = Enemy->GetComponentByClass<UActionScriptPlayerComponent>();

    UActionScriptGeneratorComponent* EnemyActionScriptGeneratorComp = Enemy->GetComponentByClass<UActionScriptGeneratorComponent>();
    EnemyActionScriptGeneratorComp->Initialize(EnemyActionScriptPlayerComp, EnemyActionPointResourceComp, EnemyGridMovementComp, StageGrid);

    Enemy->Initialize();
  }
  
  TurnManager->Initialize(Pawns);

  TurnManager->Start();

  Super::BeginPlay();
}
