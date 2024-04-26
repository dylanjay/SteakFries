// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionScriptGeneratorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionScriptGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:

	// TODO: TEMPORARY

	float MoveActionCost = 1.0f;

	float AttackActionCost = 4.0f;

	// TEMPORARY
};
