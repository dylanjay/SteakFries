// All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterManagerComponent.generated.h"

class ABattleCharacter;
class APlayerBattleCharacter;
class AEnemy;


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class STEAKFRIES_API UCharacterManagerComponent : public UActorComponent
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

	void Initialize();

	UFUNCTION(BlueprintCallable)
	TArray<ABattleCharacter*> GetAllCharacters() const { return AllCharacters; }

	UFUNCTION(BlueprintCallable)
	TArray<APlayerBattleCharacter*> GetPlayerCharacters() const { return PlayerCharacters; }

	UFUNCTION(BLueprintCallable)
	TArray<AEnemy*> GetEnemies() const { return Enemies; }

protected:

	UFUNCTION()
	void OnCharacterSpawned(ABattleCharacter* Character);

};