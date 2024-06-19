// All rights reserved

#include "StageGridManagerComponent.h"

void UStageGridManagerComponent::SpawnStageGrid()
{
	if (IsValid(StageGrid))
	{
		return;
	}

	GetWorld()->SpawnActor<AStageGrid>(StageGridClass);
	check(IsValid(StageGrid));
}
