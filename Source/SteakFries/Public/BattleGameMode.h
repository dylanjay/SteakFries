// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

// Forward Declarations
class ATurnManager;
class ACharacterSpawner;
class AStageGrid;
class AEnemyController;

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
	TSubclassOf<APawn> PlayerPawnClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Player Starting Point"))
	TArray<int> PlayerStartingPointArray = { 3, 0 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> EnemyPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyController> EnemyControllerClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Enemy Starting Point"))
	TArray<int> EnemyStartingPointArray = { 3, 5 };

protected:

	UPROPERTY()
	ATurnManager* TurnManager;

	UPROPERTY()
	ACharacterSpawner* CharacterSpawner;

	UPROPERTY()
	AStageGrid* StageGrid;

	UPROPERTY()
	APawn* PlayerPawn;

	UE::Math::TIntPoint<int>* PlayerStartingPoint;

	UE::Math::TIntPoint<int>* EnemyStartingPoint;

public:

	UFUNCTION(BlueprintCallable)
	ACharacterSpawner* GetCharacterSpawner() const;

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const;

	UFUNCTION(BlueprintCallable)
	ATurnManager* GetTurnManager() const;

	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn() const;

public:

	virtual ~ABattleGameMode();

protected:

	virtual void BeginPlay() override;
};
