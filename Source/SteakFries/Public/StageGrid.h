// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTypes.h"
#include "StageGrid.generated.h"

class AStageCell;


UCLASS()
class STEAKFRIES_API AStageGrid : public AActor
{
	GENERATED_BODY()

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
	AStageCell* GetNeighbor(AStageCell* Cell, EGridDirection Direction) const;

public:

	AStageCell* GetCell(const UE::Math::TIntPoint<int>& Point) const;

	bool IsValidPoint(const UE::Math::TIntPoint<int>& Point) const;

protected:

	void CreateGrid();

	virtual void BeginPlay() override;

};
