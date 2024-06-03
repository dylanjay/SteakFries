// Fill out your copyright notice in the Description page of Project Settings.


#include "StageCell.h"

void AStageCell::Initialize(int Col, int Row)
{
	GridPoint = new UE::Math::TIntPoint<int>(Col, Row);
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

AStageCell::~AStageCell()
{
	delete GridPoint;
}

void AStageCell::BeginPlay()
{
	Super::BeginPlay();
	
}

