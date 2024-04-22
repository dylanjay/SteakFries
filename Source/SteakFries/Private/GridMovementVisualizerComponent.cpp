// All rights reserved


#include "GridMovementVisualizerComponent.h"
#include "StageCell.h"
#include "StageGrid.h"
#include "GridMovementComponent.h"

UGridMovementVisualizerComponent::UGridMovementVisualizerComponent()
{
}

void UGridMovementVisualizerComponent::Initialize(AStageGrid* InStageGrid, UGridMovementComponent* InGridMovementComp)
{
	check(IsValid(InStageGrid));
	check(IsValid(InGridMovementComp));

	StageGrid = InStageGrid;
	GridMovementComp = InGridMovementComp;

	Reset();
}

void UGridMovementVisualizerComponent::Reset()
{
	check(IsValid(GridMovementComp));
	CurrentCell = GridMovementComp->GetCurrentCell();

	for (int i = Arrows.Num() - 1; i >= 0; i--)
	{
		GetWorld()->DestroyActor(Arrows[i]);
	}
}

bool UGridMovementVisualizerComponent::TryMoveUp()
{
	check(IsValid(CurrentCell));

	if (StageGrid->CanMoveY(CurrentCell, 1))
	{
		TArray<int> CurrentLocation = CurrentCell->GetGridLocation();
		TArray<int> Up = CurrentLocation;
		Up[1]++;

		AStageCell* UpCell = StageGrid->GetCell(Up);

		FTransform ArrowTransform;
		FVector ArrowLocation = (UpCell->GetActorLocation() + CurrentCell->GetActorLocation()) / 2;
		ArrowTransform.SetComponents(FQuat::Identity, ArrowLocation, FVector::OneVector);
		AActor* Arrow = GetWorld()->SpawnActor(ArrowClass, &ArrowTransform);
		Arrows.Add(Arrow);

		CurrentCell = UpCell;

		return true;
	}

	return false;
}

bool UGridMovementVisualizerComponent::TryMoveDown()
{
	check(IsValid(CurrentCell));
	return false;
}

bool UGridMovementVisualizerComponent::TryMoveLeft()
{
	check(IsValid(CurrentCell));
	return false;
}

bool UGridMovementVisualizerComponent::TryMoveRight()
{
	check(IsValid(CurrentCell));
	return false;
}

void UGridMovementVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
}