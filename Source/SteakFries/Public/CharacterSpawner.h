// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterPawnSpawned, APawn*, PlayerPawn, const TArray<int>&, StartLocation);

UCLASS()
class STEAKFRIES_API ACharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterSpawner();

	FOnCharacterPawnSpawned OnCharacterPawnSpawned;

public:
	APawn* SpawnCharacterPawn(const TSubclassOf<APawn>& PawnClass, const TArray<int>& StartingLocation);

protected:
	virtual void BeginPlay() override;

};
