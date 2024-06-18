// All rights reserved

#include "ActionScriptGeneratorComponent.h"
#include "ActionScriptPlayerComponent.h"
#include "ActionPointResourceComponent.h"
#include "GridMovementComponent.h"
#include "StageCell.h"
#include "MoveAction.h"
#include "StageGrid.h"
#include "BattleGameMode.h"


void UActionScriptGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UActionScriptGeneratorComponent::Initialize(UActionScriptPlayerComponent* InScriptPlayer, UActionPointResourceComponent* InActionPoints, UGridMovementComponent* InGridMovement)
{
	ScriptPlayer = InScriptPlayer;
	ScriptPlayer->OnScriptComplete.AddUniqueDynamic(this, &UActionScriptGeneratorComponent::OnPlayScriptComplete);

	ActionPoints = InActionPoints;
	GridMovement = InGridMovement;
	CurrentCell = GridMovement->GetCurrentCell();
	check(IsValid(CurrentCell));

	StageGrid = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode())->GetStageGrid();
}

void UActionScriptGeneratorComponent::Reset()
{
	if (OnReset.IsBound())
	{
		OnReset.Broadcast();
	}

	check(IsValid(ActionPoints));
	ActionPoints->Reset();

	check(IsValid(GridMovement));
	CurrentCell = GridMovement->GetCurrentCell();

	Script.Empty();
}

bool UActionScriptGeneratorComponent::TryAddAction(AAction* Action)
{
	check(IsValid(Action));
	check(IsValid(ActionPoints));

	if (!ActionPoints->CanAfford(Action->GetCost()))
	{
		return false;
	}

	Action->Initialize(StageGrid, CurrentCell);

	if (!Action->CanPlay(CurrentCell))
	{
		return false;
	}

	Script.Add(Action);

	// TODO: shouldn't be consuming here
	ActionPoints->TryConsume(Action->GetCost());

	if (Action->IsA(AMoveAction::StaticClass()))
	{
		AMoveAction* MoveAction = Cast<AMoveAction>(Action);
		CurrentCell = MoveAction->GetDestination();
		check(IsValid(CurrentCell));
	}
	
	if (OnActionAdded.IsBound())
	{
		OnActionAdded.Broadcast(Action);
	}

	return true;
}

bool UActionScriptGeneratorComponent::TryRemoveEnd()
{
	if (Script.IsEmpty())
	{
		return false;
	}

	AAction* ActionToRemove = Script.Last(0);

	check(IsValid(ActionToRemove));
	check(IsValid(ActionPoints));

	ActionPoints->Refund(ActionToRemove->GetCost());

	return true;
}

void UActionScriptGeneratorComponent::OnPlayScriptComplete()
{
	Script.Empty();

	CurrentCell = GridMovement->GetCurrentCell();
}
