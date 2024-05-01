// All rights reserved


#include "GridMovementVisualizerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "MoveAction.h"
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
}

void UGridMovementVisualizerComponent::OnScriptActionAdded(AAction* Action)
{
	check(IsValid(Action));

	if (!Action->IsA(AMoveAction::StaticClass()))
	{
		return;
	}

	AMoveAction* MoveAction = Cast<AMoveAction>(Action);

	FTransform ArrowTransform;
	FVector ArrowLocation = (MoveAction->From->GetActorLocation() + MoveAction->To->GetActorLocation()) / 2;

	FVector ArrowNormal;
	if (MoveAction->X > 0)
	{
		ArrowNormal = FVector::RightVector;
	}
	else if (MoveAction->X < 0)
	{
		ArrowNormal = FVector::LeftVector;
	}
	else if (MoveAction->Y < 0)
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