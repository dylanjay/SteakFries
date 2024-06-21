// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "BattleCharacter.h"
#include "Enemy.generated.h"

#define TPoint UE::Math::TIntPoint<int32>

class AStageGrid;
class UCharacterManagerComponent;


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

public:

	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateEnter OnStateEnterDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateExit OnStateExitDelegate;

protected:

	EEnemyState State = EEnemyState::Invalid;

	UCharacterManagerComponent* CharacterManager = nullptr;

	TPoint TargetPoint;

public:

	EEnemyState GetState() const { return State; }

	bool TrySetState(EEnemyState NewState);

	virtual void Initialize(ETeam InTeam) override;

	virtual void SetIntention();

	virtual void ExecuteTurn();

	virtual void MoveInRange();

	virtual bool TryFindTarget();

};
