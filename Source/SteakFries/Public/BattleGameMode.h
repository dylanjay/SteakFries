// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

class UTurnManagerComponent;
class UCharacterSpawnManagerComponent;
class AStageGrid;
class AEnemyController;
class AEnemy;
class APlayerBattleCharacter;

#define TPoint UE::Math::TIntPoint<int32>


UCLASS()
class STEAKFRIES_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTurnManagerComponent> TurnManagerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCharacterSpawnManagerComponent> CharacterSpawnManagerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APlayerBattleCharacter> PlayerClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Player Starting Point"))
	TArray<int32> PlayerStartingPointArray = { 3, 0 };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Enemy Starting Point"))
	TArray<int32> EnemyStartingPointArray = { 3, 5 };

protected:

	UPROPERTY()
	UTurnManagerComponent* TurnManager = nullptr;

	UPROPERTY()
	UCharacterSpawnManagerComponent* CharacterSpawnManager = nullptr;

public:

	UFUNCTION(BlueprintCallable)
	UCharacterSpawnManagerComponent* GetCharacterSpawnManager() const { return CharacterSpawnManager; }

	UFUNCTION(BlueprintCallable)
	UTurnManagerComponent* GetTurnManager() const { return TurnManager; }

protected:

	virtual void BeginPlay() override;
};
