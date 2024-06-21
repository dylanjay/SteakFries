// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTypes.h"
#include "StageCell.h"
#include "CardinalPathFinding.h"
#include "StageGrid.generated.h"

class ABattleCharacter;

#define TPoint UE::Math::TIntPoint<int32>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginCursorOverCell, AStageCell*, Cell);


UCLASS()
class STEAKFRIES_API AStageGrid : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	int32 Width = 8;

	UPROPERTY(EditDefaultsOnly)
	int32 Height = 8;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageCell> StageCellClass;

protected:

	TArray<TArray<AStageCell*>> Grid;

	TMap<AActor*, AStageCell*> CharacterCells;

	CardinalPathFinding<AStageCell>* PathFinding = nullptr;

public:

	UPROPERTY(BlueprintAssignable)
	FOnBeginCursorOverCell OnBeginCursorOverCellDelegate;
	
public:	

	bool InitializeOnGrid(ABattleCharacter* Character, const TPoint& StartingPoint);

public:

	UFUNCTION(BlueprintCallable)
	AStageCell* GetCell(const TArray<int32>& PointArray) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveX(AStageCell* FromCell, int32 X) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveY(AStageCell* FromCell, int32 Y) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveX(AStageCell* FromCell, int32 X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveY(AStageCell* FromCell, int32 Y);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* FindCharacter(AActor* Actor) const;

	UFUNCTION(BlueprintCallable)
	bool IsValidPoint(const TArray<int32>& PointArray) const;

	UFUNCTION(BlueprintCallable)
	int32 GetWidth() const { return Width; }

	UFUNCTION(BlueprintCallable)
	int32 GetHeight() const { return Height; }

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryFindPathToCell(AStageCell* Start, AStageCell* Destination, TArray<AStageCell*>& OutPath);

	UFUNCTION(BlueprintCallable)
	void OnBeginCursorOverCell(AStageCell* Cell);

public:

	AStageGrid();

	virtual ~AStageGrid();

	AStageCell* GetCell(const TPoint& Point) const;

	bool IsValidPoint(const TPoint& Point) const;

	bool IsBlocked(const TPoint& Point) const;

protected:

	void CreateGrid();

	virtual void BeginPlay() override;

};
