// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFindable2D.h"
#include "StageCell.generated.h"

class AStageGrid;


UCLASS()
class STEAKFRIES_API AStageCell : public AActor, public IPathFindable2D
{
	GENERATED_BODY()

public:

	void Initialize(AStageGrid* OwningGrid, int32 Col, int32 Row);

	void Fill(AActor* Actor);

	AActor* Empty();

protected:

	UPROPERTY(EditDefaultsOnly)
	float Width = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float Length = 100.0f;

	AStageGrid* StageGrid = nullptr;

	AActor* FillingActor = nullptr;

	UE::Math::TIntPoint<int32>* GridPoint;

public:

	UFUNCTION(BlueprintCallable)
	float GetWidth() const
	{
		return Width;
	}

	UFUNCTION(BlueprintCallable)
	float GetLength() const
	{
		return Length;
	}

	UFUNCTION(BlueprintCallable)
	virtual bool IsBlocked() const override
	{
		return FillingActor != nullptr;
	}

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const { return StageGrid; }

	UFUNCTION(BlueprintCallable)
	TArray<int32> BP_GetGridPoint() const;

public:

	virtual UE::Math::TIntPoint<int32> GetPoint() const override
	{
		return *GridPoint;
	}

	virtual ~AStageCell();

protected:
	virtual void BeginPlay() override;

};
