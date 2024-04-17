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

	UFUNCTION(BlueprintCallable)
	AStageCell* GetCell(const TArray<int>& Location);

public:

	UFUNCTION(BlueprintCallable)
	AStageCell* TryMoveX(AStageCell* FromCell, int X);

	UFUNCTION(BlueprintCallable)
	AStageCell* TryMoveY(AStageCell* FromCell, int Y);

	UFUNCTION(BlueprintCallable)
	AStageCell* FindCharacter(AActor* Actor);

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
	UFUNCTION()
	void OnPlayerPawnSpawned(APawn* PlayerPawn, const TArray<int>& StartingLocation);

	bool InitializeOnGrid(APawn* Pawn, const TArray<int>& StartingLocation);

	void CreateGrid();

	virtual void BeginPlay() override;

};
