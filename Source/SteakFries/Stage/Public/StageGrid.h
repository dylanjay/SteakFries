// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTypes.h"
#include "StageCell.h"
#include "CardinalPathFinding.h"
#include "StageGrid.generated.h"

#define TPoint UE::Math::TIntPoint<int32>


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

	bool InitializeOnGrid(APawn* Pawn, const UE::Math::TIntPoint<int32>& StartingPoint);

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

public:

	AStageGrid();

	~AStageGrid();

	AStageCell* GetCell(const UE::Math::TIntPoint<int32>& Point) const;

	bool IsValidPoint(const UE::Math::TIntPoint<int32>& Point) const;

	bool IsBlocked(const UE::Math::TIntPoint<int32>& Point) const;

	TArray<const UE::Math::TIntPoint<int32>*> GetCardinalDirections() const;

protected:

	void CreateGrid();

	virtual void BeginPlay() override;

};
