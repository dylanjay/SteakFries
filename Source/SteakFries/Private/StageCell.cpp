// Fill out your copyright notice in the Description page of Project Settings.


#include "StageCell.h"

AStageCell::AStageCell()
{

}

void AStageCell::Initialize(int Row, int Col)
{
	GridLocation = { Row, Col };
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

void AStageCell::BeginPlay()
{
	Super::BeginPlay();
	
}

