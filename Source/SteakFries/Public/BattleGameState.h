// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleGameState.generated.h"

class AStageGrid;
class AEnemy;
class ABattleCharacter;
class APlayerBattleCharacter;


UCLASS()
class STEAKFRIES_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	TArray<ABattleCharacter*> AllCharacters;

	UPROPERTY()
	TArray<APlayerBattleCharacter*> PlayerCharacters;

	UPROPERTY()
	TArray<AEnemy*> Enemies;

public:

	UFUNCTION(BlueprintCallable)
	TArray<ABattleCharacter*> GetAllCharacters () const { return AllCharacters; }

	UFUNCTION(BlueprintCallable)
	void SetAllCharacters(TArray<ABattleCharacter*> InAllCharacters) { AllCharacters = InAllCharacters; }

	UFUNCTION(BlueprintCallable)
	TArray<APlayerBattleCharacter*> GetPlayerCharacters() const { return PlayerCharacters; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerCharacters(TArray<APlayerBattleCharacter*> InPlayerCharacters) { PlayerCharacters = InPlayerCharacters; }

	UFUNCTION(BLueprintCallable)
	TArray<AEnemy*> GetEnemies() const { return Enemies; }

	UFUNCTION(BlueprintCallable)
	void SetEnemies(TArray<AEnemy*> InEnemies) { Enemies = InEnemies; }


};
