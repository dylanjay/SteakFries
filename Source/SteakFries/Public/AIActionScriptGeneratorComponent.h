// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "ActionScriptGeneratorComponent.h"
#include "AIActionScriptGeneratorComponent.generated.h"

/**
 * 
 */
UCLASS()
class STEAKFRIES_API UAIActionScriptGeneratorComponent : public UActionScriptGeneratorComponent
{
	GENERATED_BODY()
	
public:

	void GenerateMoveToTargetAndAttackScript();

protected:

	TArray<int> FindTarget();

	void MoveToTarget();

	void Attack();
};
