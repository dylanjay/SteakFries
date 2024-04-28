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
}

void UGridMovementVisualizerComponent::Reset()
{
	for (int i = Arrows.Num() - 1; i >= 0; i--)
	{
		check(IsValid(Arrows[i]));

		GetWorld()->DestroyActor(Arrows[i]);
	}
}

void UGridMovementVisualizerComponent::OnScriptActionAdded(UAction* Action)
{
	check(IsValid(Action));

	if (!Action->IsA(UMoveAction::StaticClass()))
	{
		return;
	}

	UMoveAction* MoveAction = Cast<UMoveAction>(Action);

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