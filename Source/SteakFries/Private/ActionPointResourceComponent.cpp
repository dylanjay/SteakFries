// All rights reserved


#include "ActionPointResourceComponent.h"

UActionPointResourceComponent::UActionPointResourceComponent()
{
}

void UActionPointResourceComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UActionPointResourceComponent::Reset()
{
	CurrentActionPoints = MaxActionPoints;
}

bool UActionPointResourceComponent::TryConsume(float Amount)
{
	if (Amount > CurrentActionPoints)
	{
		return false;
	}

	CurrentActionPoints -= Amount;

	return true;
}
