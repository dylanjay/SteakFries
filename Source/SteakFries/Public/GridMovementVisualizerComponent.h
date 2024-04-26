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

public:	

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

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	TArray<UPathEdge*> GetPath() const { return Path; }

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void WalkPath();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ArrowClass;

protected:

	AStageCell* CurrentCell = nullptr;

	AStageGrid* StageGrid = nullptr;

	UGridMovementComponent* GridMovementComp = nullptr;

	TArray<UPathEdge*> Path;

};

UCLASS()
class STEAKFRIES_API UPathEdge : public UObject
{
	GENERATED_BODY()

public:

	AActor* Arrow = nullptr;

	AStageCell* From = nullptr;
	AStageCell* To = nullptr;

public:

	void Initialize(AActor* InArrow, AStageCell* InFrom, AStageCell* InTo)
	{
		Arrow = InArrow;
		From = InFrom;
		To = InTo;
	};

	void Cleanup()
	{
		if (IsValid(Arrow))
		{
			Arrow->Destroy();
		}
	}
};