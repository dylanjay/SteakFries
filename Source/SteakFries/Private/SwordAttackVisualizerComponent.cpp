// All rights reserved


#include "SwordAttackVisualizerComponent.h"
#include "ActionScriptGeneratorComponent.h"
#include "MoveAction.h"
#include "StageCell.h"
#include "StageGrid.h"


void USwordAttackVisualizerComponent::Initialize(UActionScriptGeneratorComponent* InActionScriptGenerator)
{
	check(IsValid(InActionScriptGenerator));

	ActionScriptGenerator = InActionScriptGenerator;
	ActionScriptGenerator->OnActionAdded.AddUniqueDynamic(this, &USwordAttackVisualizerComponent::OnScriptActionAdded);
	ActionScriptGenerator->OnReset.AddUniqueDynamic(this, &USwordAttackVisualizerComponent::Reset);
}

void USwordAttackVisualizerComponent::Reset()
{
	if (IsValid(Visualizer))
	{
		GetWorld()->DestroyActor(Visualizer);
	}
	Visualizer = nullptr;
}

void USwordAttackVisualizerComponent::OnScriptActionAdded(AAction* Action)
{
	if (Action->IsA(AMoveAction::StaticClass()))
	{
		return;
	}

	FTransform VisualizerTransform;
	TArray<int> GridLocation = Action->CellLocation->GetGridLocation();
	GridLocation[1]++;

	AStageCell* TargetCell = Action->StageGrid->GetCell(GridLocation);

	FVector Location = TargetCell->GetActorLocation();
	VisualizerTransform.SetComponents(FQuat::Identity, Location, FVector::OneVector);
	Visualizer = GetWorld()->SpawnActor(VisualizerClass, &VisualizerTransform);
	check(IsValid(Visualizer));
}

void USwordAttackVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();
}