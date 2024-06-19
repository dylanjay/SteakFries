// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleGameState.generated.h"

class UCharacterManagerComponent;
class UStageGridManagerComponent;


UCLASS()
class STEAKFRIES_API ABattleGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UCharacterManagerComponent* CharacterManager = nullptr;

	UStageGridManagerComponent* StageGridManager = nullptr;
	
public:

	void Initialize();

	UCharacterManagerComponent* GetCharacterManager() const { return CharacterManager; }

	UStageGridManagerComponent* GetStageGridManager() const { return StageGridManager; }

};
