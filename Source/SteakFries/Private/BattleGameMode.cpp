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
  
  const FVector PlayerSpawnPoint = StageGrid->GetCell(PlayerStartingPointArray)->GetActorLocation();
  PlayerPawn = CharacterSpawner->SpawnCharacterPawn(PlayerPawnClass, PlayerSpawnPoint);
  check(IsValid(PlayerPawn));

  PlayerController->Possess(PlayerPawn);

  Pawns.Add(PlayerPawn);

  PlayerStartingPoint = new UE::Math::TIntPoint<int>(PlayerStartingPointArray[0], PlayerStartingPointArray[1]);
  StageGrid->InitializeOnGrid(PlayerPawn, *PlayerStartingPoint);

  UGridMovementVisualizerComponent* GridMovementVisualizerComp = PlayerPawn->GetComponentByClass<UGridMovementVisualizerComponent>();
  check(IsValid(GridMovementVisualizerComp));

  UGridMovementComponent* GridMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));

  UActionPointResourceComponent* ActionPointResourceComp = PlayerPawn->GetComponentByClass<UActionPointResourceComponent>();

  UActionScriptPlayerComponent* ActionScriptPlayerComp = PlayerPawn->GetComponentByClass<UActionScriptPlayerComponent>();

  UActionScriptGeneratorComponent* ActionScriptGeneratorComp = PlayerPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
  ActionScriptGeneratorComp->Initialize(ActionScriptPlayerComp, ActionPointResourceComp, GridMovementComp, StageGrid);

  USwordAttackVisualizerComponent* SwordAttackVisualizerComp = PlayerPawn->GetComponentByClass<USwordAttackVisualizerComponent>();
  SwordAttackVisualizerComp->Initialize(StageGrid, ActionScriptGeneratorComp);

  GridMovementVisualizerComp->Initialize(ActionScriptGeneratorComp);
  
  if (IsValid(EnemyPawnClass))
  {
    const FVector EnemySpawnPoint = StageGrid->GetCell(EnemyStartingPointArray)->GetActorLocation();
    APawn* EnemyPawn = CharacterSpawner->SpawnCharacterPawn(EnemyPawnClass, EnemySpawnPoint);
    check(IsValid(EnemyPawn));

    AEnemyController* EnemyController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
    check(IsValid(EnemyController));

    EnemyController->Possess(EnemyPawn);
    EnemyController->Initialize(StageGrid);

    Pawns.Add(EnemyPawn);

    EnemyStartingPoint = new UE::Math::TIntPoint<int>(EnemyStartingPointArray[0], EnemyStartingPointArray[1]);
    StageGrid->InitializeOnGrid(EnemyPawn, *EnemyStartingPoint);

    UGridMovementComponent* EnemyGridMovementComp = EnemyPawn->GetComponentByClass<UGridMovementComponent>();
    check(IsValid(EnemyGridMovementComp));

    UActionPointResourceComponent* EnemyActionPointResourceComp = EnemyPawn->GetComponentByClass<UActionPointResourceComponent>();

    UActionScriptPlayerComponent* EnemyActionScriptPlayerComp = EnemyPawn->GetComponentByClass<UActionScriptPlayerComponent>();

    UActionScriptGeneratorComponent* EnemyActionScriptGeneratorComp = EnemyPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
    EnemyActionScriptGeneratorComp->Initialize(EnemyActionScriptPlayerComp, EnemyActionPointResourceComp, EnemyGridMovementComp, StageGrid);
  }
  
  TurnManager->Initialize(Pawns);

  TurnManager->Start();

  Super::BeginPlay();
}
