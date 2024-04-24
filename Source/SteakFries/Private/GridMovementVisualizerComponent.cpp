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

	for (int i = Path.Num() - 1; i >= 0; i--)
	{
		check(IsValid(Path[i]));
		Path[i]->Cleanup();
	}
	Path.Empty();
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
		check(IsValid(Arrow));

		UPathEdge* PathEdge = NewObject<UPathEdge>();
		check(IsValid(PathEdge));

		PathEdge->Initialize(Arrow, CurrentCell, UpCell);
		Path.Add(PathEdge);

		CurrentCell = UpCell;

		return true;
	}

	return false;
}

bool UGridMovementVisualizerComponent::TryMoveDown()
{
	check(IsValid(CurrentCell));

	if (StageGrid->CanMoveY(CurrentCell, -1))
	{
		TArray<int> CurrentLocation = CurrentCell->GetGridLocation();
		TArray<int> Down = CurrentLocation;
		Down[1]--;

		AStageCell* DownCell = StageGrid->GetCell(Down);

		FTransform ArrowTransform;
		FVector ArrowLocation = (DownCell->GetActorLocation() + CurrentCell->GetActorLocation()) / 2;
		ArrowTransform.SetComponents(FQuat::FindBetweenNormals(FVector::ForwardVector, FVector::BackwardVector), ArrowLocation, FVector::OneVector);
		AActor* Arrow = GetWorld()->SpawnActor(ArrowClass, &ArrowTransform);
		check(IsValid(Arrow));

		UPathEdge* PathEdge = NewObject<UPathEdge>();
		check(IsValid(PathEdge));
		
		PathEdge->Initialize(Arrow, CurrentCell, DownCell);
		Path.Add(PathEdge);

		CurrentCell = DownCell;

		return true;
	}

	return false;
}

bool UGridMovementVisualizerComponent::TryMoveLeft()
{
	check(IsValid(CurrentCell));

	if (StageGrid->CanMoveX(CurrentCell, -1))
	{
		TArray<int> CurrentLocation = CurrentCell->GetGridLocation();
		TArray<int> Left = CurrentLocation;
		Left[0]--;

		AStageCell* LeftCell = StageGrid->GetCell(Left);

		FTransform ArrowTransform;
		FVector ArrowLocation = (LeftCell->GetActorLocation() + CurrentCell->GetActorLocation()) / 2;
		ArrowTransform.SetComponents(FQuat::FindBetweenNormals(FVector::ForwardVector, FVector::LeftVector), ArrowLocation, FVector::OneVector);
		AActor* Arrow = GetWorld()->SpawnActor(ArrowClass, &ArrowTransform);
		check(IsValid(Arrow));

		UPathEdge* PathEdge = NewObject<UPathEdge>();
		check(IsValid(PathEdge));

		PathEdge->Initialize(Arrow, CurrentCell, LeftCell);
		Path.Add(PathEdge);

		CurrentCell = LeftCell;

		return true;
	}

	return false;
}

bool UGridMovementVisualizerComponent::TryMoveRight()
{
	check(IsValid(CurrentCell));

	if (StageGrid->CanMoveX(CurrentCell, 1))
	{
		TArray<int> CurrentLocation = CurrentCell->GetGridLocation();
		TArray<int> Right = CurrentLocation;
		Right[0]++;

		AStageCell* RightCell = StageGrid->GetCell(Right);

		FTransform ArrowTransform;
		FVector ArrowLocation = (RightCell->GetActorLocation() + CurrentCell->GetActorLocation()) / 2;
		ArrowTransform.SetComponents(FQuat::FindBetweenNormals(FVector::ForwardVector, FVector::RightVector), ArrowLocation, FVector::OneVector);
		AActor* Arrow = GetWorld()->SpawnActor(ArrowClass, &ArrowTransform);
		check(IsValid(Arrow));

		UPathEdge* PathEdge = NewObject<UPathEdge>();
		check(IsValid(PathEdge));

		PathEdge->Initialize(Arrow, CurrentCell, RightCell);
		Path.Add(PathEdge);

		CurrentCell = RightCell;

		return true;
	}

	return false;
}

void UGridMovementVisualizerComponent::WalkPath()
{
	if (Path.IsEmpty())
	{
		return;
	}

	UPathEdge* Head = Path[0];

	check(IsValid(Head));
	check(IsValid(Head->To));
	check(IsValid(GridMovementComp));

	if (GridMovementComp->TryMoveToCell(Head->To))
	{
		Head->Cleanup();
		Path.RemoveAt(0);
	}
}

void UGridMovementVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
}