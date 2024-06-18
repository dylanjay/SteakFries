// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionScriptGeneratorComponent.generated.h"

class AAction;
class UActionScriptPlayerComponent;
class UActionPointResourceComponent;
class UGridMovementComponent;
class AStageCell;
class AStageGrid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionAdded, AAction*, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset);


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionScriptGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnActionAdded OnActionAdded;

	FOnReset OnReset;

public:

	void Initialize(UActionScriptPlayerComponent* InScriptPlayer, UActionPointResourceComponent* InActionPoints, UGridMovementComponent* InGridMovement);

public:

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	bool TryAddAction(AAction* Action);

	UFUNCTION(BlueprintCallable)
	bool TryRemoveEnd();

	UFUNCTION(BlueprintCallable)
	TArray<AAction*> GetScript() const { return Script; }

	UFUNCTION()
	void OnPlayScriptComplete();

protected:
	virtual void BeginPlay() override;

protected:

	UActionScriptPlayerComponent* ScriptPlayer = nullptr;

	UActionPointResourceComponent* ActionPoints = nullptr;

	UGridMovementComponent* GridMovement = nullptr;

	AStageGrid* StageGrid = nullptr;

	TArray<AAction*> Script;

	AStageCell* CurrentCell;
};
