// Fill out your copyright notice in the Description page of Project Settings.


#include "StageCell.h"

void AStageCell::Initialize(AStageGrid* OwningGrid, int32 Col, int32 Row)
{
	check(IsValid(OwningGrid));
	StageGrid = OwningGrid;
	GridPoint = new UE::Math::TIntPoint<int32>(Col, Row);
}

void AStageCell::Fill(AActor* Actor)
{
	if (IsValid(Actor))
	{
		FillingActor = Actor;
	}
}

AActor* AStageCell::Empty()
{
	AActor* Actor = FillingActor;
	FillingActor = nullptr;
	return Actor;
}

TArray<int32> AStageCell::BP_GetGridPoint() const
{
	TArray<int32> Array = { GridPoint->X, GridPoint->Y, };
	return Array;
}

AStageCell::~AStageCell()
{
	delete GridPoint;
}

void AStageCell::BeginPlay()
{
	Super::BeginPlay();
	
}

