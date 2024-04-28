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

void UActionPointResourceComponent::Refund(float Amount)
{
	CurrentActionPoints = FMath::Clamp(CurrentActionPoints + Amount, 0.0f, MaxActionPoints);
}
