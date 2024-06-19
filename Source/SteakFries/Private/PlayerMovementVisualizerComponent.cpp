// All rights reserved


#include "PlayerMovementVisualizerComponent.h"
#include "PlayerControllerBase.h"
#include "StageGrid.h"

void UPlayerMovementVisualizerComponent::Initialize(APlayerControllerBase* InPlayerController, AStageGrid* InStageGrid)
{
	PlayerController = InPlayerController;
	PlayerController->OnStateChangeDelegate.AddUniqueDynamic(this, &UPlayerMovementVisualizerComponent::OnPlayerControllerStateChange);

	StageGrid = InStageGrid;
}

void UPlayerMovementVisualizerComponent::OnPlayerControllerStateChange(EPlayerControllerState NewState)
{
	if (NewState == EPlayerControllerState::Movement)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

void UPlayerMovementVisualizerComponent::ActivateVisual()
{
	if (bIsActive)
	{
		return;
	}


}

void UPlayerMovementVisualizerComponent::DeactivateVisual()
{
	if (!bIsActive)
	{
		return;
	}
}