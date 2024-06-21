// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnManagerComponent.generated.h"

class AEnemyController;
class ABattleCharacter;
class UCharacterManagerComponent;
class APlayerControllerBase;

UENUM(BlueprintType)
enum class ETurnManagerState : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	FillingTurnQueue,
	SetEnemyIntentions UMETA(DisplayName = "Set Enemy Intentions"),
	TurnCycle UMETA(DisplayName = "Turn Cycle"),
};


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class STEAKFRIES_API UTurnManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	ETurnManagerState State = ETurnManagerState::Invalid;

	TQueue<ABattleCharacter*> TurnQueue;

	ABattleCharacter* CurrentTurnCharacter = nullptr;

	UCharacterManagerComponent* CharacterManager = nullptr;

	APlayerControllerBase* PlayerController = nullptr;
	
public:	

	virtual void BeginPlay() override;

	void Initialize();

	void Start();

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void EndTurn();

protected:

	bool TrySetState(ETurnManagerState NewState);

	bool TrySetStateNextTick(ETurnManagerState NewState);

	void SetEnemyIntentions();

	void NextTurn();

	void FillTurnQueue();

	UFUNCTION()
	void OnEnemyStateEnter(AEnemy* Enemy, EEnemyState NewState);

};
