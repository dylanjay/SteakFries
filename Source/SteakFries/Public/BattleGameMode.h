// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

// Forward Declarations
class ACharacterSpawner;
class AStageGrid;

UCLASS()
class STEAKFRIES_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterSpawner> CharacterSpawnerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageGrid> StageGridClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<int> StartingPlayerLocation = { 7, 3 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> EnemyPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<int> StartingEnemyLocation = { 3, 3 };

protected:

	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn() const;

protected:

	ACharacterSpawner* CharacterSpawner;

	AStageGrid* StageGrid;

	APawn* PlayerPawn;

protected:

	virtual void BeginPlay() override;
};
