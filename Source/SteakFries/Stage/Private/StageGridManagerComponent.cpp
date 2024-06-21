// All rights reserved

#include "StageGridManagerComponent.h"
#include "StageGrid.h"

void UStageGridManagerComponent::SpawnStageGrid()
{
	if (IsValid(StageGrid))
	{
		return;
	}

	StageGrid = GetWorld()->SpawnActor<AStageGrid>(StageGridClass);
	check(IsValid(StageGrid));
}
