// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

class AEnemyController;

UENUM(BlueprintType)
enum class ETurnManagerState : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	SetEnemyIntentions UMETA(DisplayName = "Set Enemy Intentions"),
	TurnCycle UMETA(DisplayName = "Turn Cycle"),
};


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	

	void Initialize(TArray<APawn*> Pawns);

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

protected:

	ETurnManagerState State = ETurnManagerState::Invalid;

	TQueue<APawn*> TurnQueue;

	TArray<AEnemyController*> EnemyControllers;

	APawn* CurrentTurnPawn = nullptr;
};
