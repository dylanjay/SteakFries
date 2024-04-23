// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementVisualizerComponent.generated.h"

// Forward Declarations
class AStageCell;
class AStageGrid;
class UGridMovementComponent;


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UGridMovementVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ArrowClass;

public:	

	UGridMovementVisualizerComponent();

	void Initialize(AStageGrid* InStageGrid, UGridMovementComponent* InGridMovementComp);

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveUp();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveDown();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveLeft();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryMoveRight();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	AStageCell* CurrentCell;

	UPROPERTY()
	AStageGrid* StageGrid;

	UPROPERTY()
	UGridMovementComponent* GridMovementComp;

	UPROPERTY()
	TArray<AActor*> Arrows;

};
