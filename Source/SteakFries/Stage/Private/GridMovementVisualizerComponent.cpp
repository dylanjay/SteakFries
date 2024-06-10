// All rights reserved


#include "GridMovementVisualizerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "SingleMoveAction.h"
#include "StageCell.h"


void UGridMovementVisualizerComponent::Initialize(UActionScriptGeneratorComponent* InActionScriptGenerator)
{
	check(IsValid(InActionScriptGenerator));

	ActionScriptGenerator = InActionScriptGenerator;
	ActionScriptGenerator->OnActionAdded.AddUniqueDynamic(this, &UGridMovementVisualizerComponent::OnScriptActionAdded);
	ActionScriptGenerator->OnReset.AddUniqueDynamic(this, &UGridMovementVisualizerComponent::Reset);
}

void UGridMovementVisualizerComponent::Reset()
{
	for (int i = Arrows.Num() - 1; i >= 0; i--)
	{
		GetWorld()->DestroyActor(Arrows[i]);
	}

	Arrows.Empty();
}

void UGridMovementVisualizerComponent::OnScriptActionAdded(AAction* Action)
{
	check(IsValid(Action));

	if (!Action->IsA(ASingleMoveAction::StaticClass()))
	{
		return;
	}

	ASingleMoveAction* SingleMoveAction = Cast<ASingleMoveAction>(Action);

	AStageCell* ActionStart = SingleMoveAction->GetCellLocation();
	check(IsValid(ActionStart));

	AStageCell* Destination = SingleMoveAction->GetDestination();
	check(IsValid(Destination));

	FTransform ArrowTransform;
	FVector ArrowLocation = (ActionStart->GetActorLocation() + Destination->GetActorLocation()) / 2;

	FVector ArrowNormal;
	if (SingleMoveAction->X > 0)
	{
		ArrowNormal = FVector::RightVector;
	}
	else if (SingleMoveAction->X < 0)
	{
		ArrowNormal = FVector::LeftVector;
	}
	else if (SingleMoveAction->Y < 0)
	{
		ArrowNormal = FVector::BackwardVector;
	}
	else
	{
		ArrowNormal = FVector::ForwardVector;
	}

	FQuat ArrowRotation = FQuat::FindBetweenNormals(FVector::ForwardVector, ArrowNormal);
	ArrowTransform.SetComponents(ArrowRotation, ArrowLocation, FVector::OneVector);
	AActor* Arrow = GetWorld()->SpawnActor(ArrowClass, &ArrowTransform);
	check(IsValid(Arrow));
	Arrows.Add(Arrow);
}

void UGridMovementVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
}