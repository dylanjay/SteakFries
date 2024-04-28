// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageGrid.generated.h"

// Forward Declarations
class AStageCell;

UCLASS()
class STEAKFRIES_API AStageGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	bool InitializeOnGrid(APawn* Pawn, const TArray<int>& StartingLocation);

public:

	UFUNCTION(BlueprintCallable)
	AStageCell* GetCell(const TArray<int>& Location);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveX(AStageCell* FromCell, int X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool CanMoveY(AStageCell* FromCell, int Y);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveX(AStageCell* FromCell, int X);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* TryMoveY(AStageCell* FromCell, int Y);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AStageCell* FindCharacter(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	bool IsValidLocation(const TArray<int>& Location) const;

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

protected:

	void CreateGrid();

	virtual void BeginPlay() override;

};
