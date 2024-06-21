// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "StageGridManagerComponent.h"
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

	UPROPERTY()
	UStageGridManagerComponent* StageGridManager = nullptr;
	
public:

	void Initialize();

	UFUNCTION(BlueprintCallable)
	UCharacterManagerComponent* GetCharacterManager() const { return CharacterManager; }

	UFUNCTION(BlueprintCallable)
	AStageGrid* GetStageGrid() const { return StageGridManager->GetStageGrid(); }

};
