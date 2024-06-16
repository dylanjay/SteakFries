// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

#define TPoint UE::Math::TIntPoint<int32>

class AStageGrid;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Invalid UMETA(DisplayName = "Invalid"),
	Default UMETA(DisplayName = "Default"),
	SettingIntention UMETA(DisplayName = "Setting Intention"),
	IntentionSet,
	ExecutingTurn UMETA(DisplayName = "Executing Turn"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyStateEnter, EEnemyState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyStateExit, EEnemyState, OldState);


UCLASS()
class STEAKFRIES_API AEnemy : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateEnter OnEnemyStateEnterDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateExit OnEnemyStateExitDelegate;

protected:

	EEnemyState State = EEnemyState::Invalid;

	TPoint TargetPoint;

public:

	EEnemyState GetState() const { return State; }

	bool TrySetState(EEnemyState NewState);

	virtual void Initialize();

	virtual void SetIntention();

	virtual void ExecuteTurn();

	virtual void MoveInRange();

	virtual void TryFindTarget();

};
