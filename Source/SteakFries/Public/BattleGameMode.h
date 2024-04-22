// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

// Forward Declarations
class ATurnManager;
class ACharacterSpawner;
class AStageGrid;

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

	UPROPERTY(EditDefaultsOnly)
	TArray<int> StartingPlayerLocation = { 3, 0 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> EnemyPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<int> StartingEnemyLocation = { 3, 5 };

protected:

	UFUNCTION(BlueprintCallable)
	ACharacterSpawner* GetCharacterSpawner() const;

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const;

	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn() const;

protected:

	UPROPERTY()
	ATurnManager* TurnManager;

	UPROPERTY()
	ACharacterSpawner* CharacterSpawner;

	UPROPERTY()
	AStageGrid* StageGrid;

	UPROPERTY()
	APawn* PlayerPawn;

protected:

	virtual void BeginPlay() override;
};
