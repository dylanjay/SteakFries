// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageCell.generated.h"

UCLASS()
class STEAKFRIES_API AStageCell : public AActor
{
	GENERATED_BODY()

public:

	void Initialize(int Col, int Row);

	void Fill(AActor* Actor);

	AActor* Empty();

protected:

	UPROPERTY(EditDefaultsOnly)
	float Width = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float Length = 100.0f;

	AActor* FillingActor;

	UE::Math::TIntPoint<int>* GridPoint;

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
	bool IsFilled() const
	{
		return FillingActor != nullptr;
	}

	UFUNCTION(BlueprintCallable)
	TArray<int> BP_GetGridPoint() const
	{
		TArray<int> Array;
		Array.Init(GridPoint->X, GridPoint->Y);
		return Array;
	}

public:

	UE::Math::TIntPoint<int> GetGridPoint() const
	{
		return *GridPoint;
	}

	virtual ~AStageCell();

protected:
	virtual void BeginPlay() override;

};
