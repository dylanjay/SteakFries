// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGameMode.generated.h"

// Forward Declarations
class ACharacterSpawner;
class AStageGrid;

UCLASS()
class STEAKFRIES_API ABattleGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacterSpawner> CharacterSpawnerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AStageGrid> StageGridClass;

protected:

	UFUNCTION(BlueprintCallable)
	APawn* GetPlayerPawn() const;

protected:

	ACharacterSpawner* CharacterSpawner;

	AStageGrid* StageGrid;

	APawn* PlayerPawn;

protected:

	virtual void BeginPlay() override;
};
