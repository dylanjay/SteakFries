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
	AStageCell();

	void Initialize(int InRow, int InCol);

	void Fill(AActor* Actor);

	AActor* Empty();

protected:

	UPROPERTY(EditDefaultsOnly)
	float Width = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float Length = 100.0f;

	AActor* FillingActor;

	int Row;

	int Col;

public:

	float GetWidth() const
	{
		return Width;
	}

	float GetLength() const
	{
		return Length;
	}

	bool IsFilled() const
	{
		return FillingActor != nullptr;
	}

	int GetRow() const
	{
		return Row;
	}

	int GetCol() const
	{
		return Col;
	}

protected:
	virtual void BeginPlay() override;

};
