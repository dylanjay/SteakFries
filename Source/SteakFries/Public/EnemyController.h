// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class APawn;
class ATurnManager;
class UAIActionScriptGeneratorComponent;
class UActionScriptComponent;

/**
 * 
 */
UCLASS()
class STEAKFRIES_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void SetPawn(APawn* InPawn) override;

	void TakeTurn();

protected:

	UFUNCTION()
	void OnScriptComplete();

protected:

	ATurnManager* TurnManager = nullptr;

	UAIActionScriptGeneratorComponent* ActionScriptGenerator = nullptr;

	UActionScriptComponent* ActionScript = nullptr;
};
