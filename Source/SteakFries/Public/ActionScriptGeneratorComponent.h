// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionScriptGeneratorComponent.generated.h"

class UAction;
class UActionPointResourceComponent;
class UGridMovementComponent;
class AStageCell;
class AStageGrid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionAdded, UAction*, Action);


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionScriptGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	FOnActionAdded OnActionAdded;

public:

	void Initialize(UActionPointResourceComponent* InActionPoints, UGridMovementComponent* InGridMovement, AStageGrid* InStageGrid);

public:

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	bool TryAddAction(UAction* Action);

	UFUNCTION(BlueprintCallable)
	bool TryRemoveEnd();

protected:
	virtual void BeginPlay() override;

protected:

	UActionPointResourceComponent* ActionPoints = nullptr;

	UGridMovementComponent* GridMovement = nullptr;

	AStageGrid* StageGrid = nullptr;

	TArray<UAction*> Script;

	AStageCell* CurrentCell;
};
