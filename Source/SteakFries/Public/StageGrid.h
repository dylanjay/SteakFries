// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTypes.h"
#include "StageCell.h"
#include "StageGrid.generated.h"

#define TPoint UE::Math::TIntPoint<int>


UCLASS()
class STEAKFRIES_API AStageGrid : public AActor
{
	GENERATED_BODY()

	struct CellSearchData
	{
		AStageCell* Cell = nullptr;
		AStageCell* Parent = nullptr;

		bool Visited = false;

		float Cost = FLT_MAX;
		float MoveCost = FLT_MAX;
		float HeuristicCost = FLT_MAX;

		CellSearchData(AStageCell* InCell)
		{
			Cell = InCell;
		}

		static bool Compare(const CellSearchData &left, const CellSearchData &right)
		{
			return left.Cost <= right.Cost;
		}

		float CalculateHeuristicCost(AStageCell* Destination)
		{
			// Manhattan Distance
			TPoint CellPoint = Cell->GetGridPoint();
			TPoint DestinationPoint = Destination->GetGridPoint();
			return std::abs(CellPoint.X - DestinationPoint.X) + std::abs(CellPoint.Y - DestinationPoint.Y);
		}
	};

protected:

	UPROPERTY(EditDefaultsOnly)
	int Width = 8;

	UPROPERTY(EditDefaultsOnly)
	int Height = 8;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageCell> StageCellClass;

protected:

	TArray<TArray<AStageCell*>> Grid;

	TMap<AActor*, AStageCell*> CharacterCells;

	TArray<const UE::Math::TIntPoint<int>*> CardinalDirections;
	
public:	

	bool InitializeOnGrid(APawn* Pawn, const UE::Math::TIntPoint<int>& StartingPoint);

public:

	UFUNCTION(BlueprintCallable)
	AStageCell* GetCell(const TArray<int>& PointArray) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveX(AStageCell* FromCell, int X) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveY(AStageCell* FromCell, int Y) const;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveX(AStageCell* FromCell, int X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveY(AStageCell* FromCell, int Y);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* FindCharacter(AActor* Actor) const;

	UFUNCTION(BlueprintCallable)
	bool IsValidPoint(const TArray<int>& PointArray) const;

	UFUNCTION(BlueprintCallable)
	int GetWidth() const { return Width; }

	UFUNCTION(BlueprintCallable)
	int GetHeight() const { return Height; }

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TryFindPathToCell(AStageCell* Start, AStageCell* Destination, TArray<AStageCell*>& OutPath);

public:

	AStageGrid();

	AStageCell* GetCell(const UE::Math::TIntPoint<int>& Point) const;

	bool IsValidPoint(const UE::Math::TIntPoint<int>& Point) const;

	bool IsFilled(const UE::Math::TIntPoint<int>& Point) const;

	TArray<const UE::Math::TIntPoint<int>*> GetCardinalDirections() const { return CardinalDirections; }

protected:

	void CreateGrid();

	virtual void BeginPlay() override;

	TArray<AStageCell*> TracePath(const TArray<TArray<CellSearchData>>& DataMatrix, AStageCell* Start, AStageCell* Destination);

};
