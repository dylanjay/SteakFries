// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMovement.h"
#include "StageGrid.h"
#include "StageCell.h"

UGridMovement::UGridMovement()
{

}

void UGridMovement::Initialize(AStageGrid* InStageGrid, AStageCell* InStageCell)
{
	StageGrid = InStageGrid;
	StageCell = InStageCell;
}

void UGridMovement::TryMoveX(int X)
{
	StageCell = StageGrid->TryMoveX(StageCell, X);
	GetOwner()->SetActorLocation(StageCell->GetActorLocation());
}

void UGridMovement::TryMoveY(int Y)
{
	StageCell = StageGrid->TryMoveY(StageCell, Y);
	GetOwner()->SetActorLocation(StageCell->GetActorLocation());
}

void UGridMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

