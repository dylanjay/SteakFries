// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnManagerComponent.generated.h"

class AEnemyController;
class ABattleCharacter;
class UCharacterManagerComponent;

UENUM(BlueprintType)
enum class ETurnManagerState : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	SetEnemyIntentions UMETA(DisplayName = "Set Enemy Intentions"),
	TurnCycle UMETA(DisplayName = "Turn Cycle"),
};


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API UTurnManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	ETurnManagerState State = ETurnManagerState::Invalid;

	TQueue<ABattleCharacter*> TurnQueue;

	ABattleCharacter* CurrentTurnCharacter = nullptr;

	UCharacterManagerComponent* CharacterManager = nullptr;
	
public:	

	virtual void BeginPlay() override;

	void Initialize();

	void Start();

	void SetEnemyIntentions();

	void NextTurn();

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	bool TryGetEnemyController(AController* Controller, AEnemyController*& OutEnemyController);

protected:

	bool TrySetState(ETurnManagerState NewState);

	UFUNCTION()
	void OnEnemyStateEnter(AEnemy* Enemy, EEnemyState NewState);

};
