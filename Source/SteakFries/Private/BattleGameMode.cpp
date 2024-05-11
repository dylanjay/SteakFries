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

void ABattleGameMode::BeginPlay()
{
  TurnManager = GetWorld()->SpawnActor<ATurnManager>(TurnManagerClass);

  TArray<APawn*> Pawns;

  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

  CharacterSpawner = GetWorld()->SpawnActor<ACharacterSpawner>(CharacterSpawnerClass);
  check(IsValid(CharacterSpawner));

  StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);
  check(IsValid(StageGrid));
  
  const FVector PlayerSpawnLocation = StageGrid->GetCell(StartingPlayerLocation)->GetActorLocation();
  PlayerPawn = CharacterSpawner->SpawnCharacterPawn(PlayerPawnClass, PlayerSpawnLocation);
  check(IsValid(PlayerPawn));

  PlayerController->Possess(PlayerPawn);

  Pawns.Add(PlayerPawn);

  StageGrid->InitializeOnGrid(PlayerPawn, StartingPlayerLocation);

  UGridMovementVisualizerComponent* GridMovementVisualizerComp = PlayerPawn->GetComponentByClass<UGridMovementVisualizerComponent>();
  check(IsValid(GridMovementVisualizerComp));

  UGridMovementComponent* GridMovementComp = PlayerPawn->GetComponentByClass<UGridMovementComponent>();
  check(IsValid(GridMovementComp));

  UActionPointResourceComponent* ActionPointResourceComp = PlayerPawn->GetComponentByClass<UActionPointResourceComponent>();

  UActionScriptGeneratorComponent* ActionScriptGeneratorComp = PlayerPawn->GetComponentByClass<UActionScriptGeneratorComponent>();
  ActionScriptGeneratorComp->Initialize(ActionPointResourceComp, GridMovementComp, StageGrid);

  USwordAttackVisualizerComponent* SwordAttackVisualizerComp = PlayerPawn->GetComponentByClass<USwordAttackVisualizerComponent>();
  SwordAttackVisualizerComp->Initialize(ActionScriptGeneratorComp);

  GridMovementVisualizerComp->Initialize(ActionScriptGeneratorComp);
  
  if (IsValid(EnemyPawnClass))
  {
    const FVector EnemySpawnLocation = StageGrid->GetCell(StartingEnemyLocation)->GetActorLocation();
    APawn* EnemyPawn = CharacterSpawner->SpawnCharacterPawn(EnemyPawnClass, EnemySpawnLocation);
    check(IsValid(EnemyPawn));

    AEnemyController* EnemyController = GetWorld()->SpawnActor<AEnemyController>(EnemyControllerClass);
    check(IsValid(EnemyController));

    EnemyController->SetPawn(EnemyPawn);

    Pawns.Add(EnemyPawn);

    StageGrid->InitializeOnGrid(EnemyPawn, StartingEnemyLocation);
  }
  
  TurnManager->Initialize(Pawns);

  TurnManager->Start();

  Super::BeginPlay();
}
