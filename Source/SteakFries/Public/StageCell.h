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

	void Initialize(int Row, int Col);

	void Fill(AActor* Actor);

	AActor* Empty();

protected:

	UPROPERTY(EditDefaultsOnly)
	float Width = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float Length = 100.0f;

	AActor* FillingActor;

	TArray<int> GridLocation;

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
	TArray<int> GetGridLocation() const
	{
		return GridLocation;
	}

protected:
	virtual void BeginPlay() override;

};
