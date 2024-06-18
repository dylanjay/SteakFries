// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BattleCharacter.generated.h"

class UGridMovementComponent;
class UActionPointResourceComponent;
class UActionScriptGeneratorComponent;
class UActionScriptPlayerComponent;


UCLASS()
class STEAKFRIES_API ABattleCharacter : public APaperCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	AStageGrid* StageGrid = nullptr;

	UPROPERTY();
	UGridMovementComponent* GridMovementComp = nullptr;

	UPROPERTY();
	UActionPointResourceComponent* ActionPointsComp = nullptr;

	UPROPERTY();
	UActionScriptPlayerComponent* ActionScriptPlayerComp = nullptr;

	UPROPERTY();
	UActionScriptGeneratorComponent* ActionScriptGeneratorComp = nullptr;

public:
	virtual void Initialize();
};
