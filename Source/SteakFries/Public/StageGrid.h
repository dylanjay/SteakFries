// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageGrid.generated.h"

// Forward Declarations
class AStageCell;
class ACharacterSpawner;

UCLASS()
class STEAKFRIES_API AStageGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	AStageGrid();

	void Initialize(ACharacterSpawner* CharacterSpawner);

	AStageCell* TryMoveX(AStageCell* FromCell, int X);

	AStageCell* TryMoveY(AStageCell* FromCell, int Y);

protected:

	UPROPERTY(EditDefaultsOnly)
	int Width = 8;

	UPROPERTY(EditDefaultsOnly)
	int Height = 8;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageCell> StageCellClass;

protected:

	TArray<TArray<AStageCell*>> Grid;

protected:
	UFUNCTION()
	void OnPlayerPawnSpawned(APawn* PlayerPawn);

	bool InitializeOnGrid(APawn* Pawn, int Row, int Col);

	void CreateGrid();

	virtual void BeginPlay() override;

};
