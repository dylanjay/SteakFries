// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "BattleCharacter.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyStateEnter, AEnemy*, Enemy, EEnemyState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyStateExit, AEnemy*, Enemy, EEnemyState, OldState);


UCLASS()
class STEAKFRIES_API AEnemy : public ABattleCharacter
{
	GENERATED_BODY()

protected:

	EEnemyState State = EEnemyState::Invalid;

	FOnEnemyStateEnter OnStateEnterDelegate;

	FOnEnemyStateExit OnStateExitDelegate;

	TPoint TargetPoint;

public:

	EEnemyState GetState() const { return State; }

	FOnEnemyStateEnter GetOnStateEnterDelegate() const { return OnStateEnterDelegate; }

	FOnEnemyStateExit GetOnStateExitDelegate() const { return OnStateExitDelegate; }

	bool TrySetState(EEnemyState NewState);

	virtual void Initialize() override;

	virtual void SetIntention();

	virtual void ExecuteTurn();

	virtual void MoveInRange();

	virtual bool TryFindTarget();

};
