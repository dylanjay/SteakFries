// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPawnSpawned, APawn*, PlayerPawn);

UCLASS()
class STEAKFRIES_API ACharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterSpawner();

	FOnPlayerPawnSpawned OnPlayerPawnSpawned;

public:
	APawn* SpawnPlayerPawn();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawnClass;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<APawn>> EnemyPawnClasses;

protected:
	virtual void BeginPlay() override;

};
