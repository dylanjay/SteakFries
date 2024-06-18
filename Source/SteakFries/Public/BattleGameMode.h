// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

class ATurnManager;
class ACharacterSpawner;
class AStageGrid;
class AEnemyController;
class AEnemy;
class APlayerBattleCharacter;


UCLASS()
class STEAKFRIES_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATurnManager> TurnManagerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterSpawner> CharacterSpawnerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageGrid> StageGridClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerBattleCharacter> PlayerClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Player Starting Point"))
	TArray<int32> PlayerStartingPointArray = { 3, 0 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyController> EnemyControllerClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Enemy Starting Point"))
	TArray<int32> EnemyStartingPointArray = { 3, 5 };

protected:

	UPROPERTY()
	ATurnManager* TurnManager;

	UPROPERTY()
	ACharacterSpawner* CharacterSpawner;

	UPROPERTY()
	AStageGrid* StageGrid;

	UE::Math::TIntPoint<int32>* PlayerStartingPoint;

	UE::Math::TIntPoint<int32>* EnemyStartingPoint;

public:

	UFUNCTION(BlueprintCallable)
	ACharacterSpawner* GetCharacterSpawner() const { return CharacterSpawner; }

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const { return StageGrid; }

	UFUNCTION(BlueprintCallable)
	ATurnManager* GetTurnManager() const { return TurnManager; }

public:

	virtual ~ABattleGameMode();

protected:

	virtual void BeginPlay() override;
};
