// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterSpawner.generated.h"


UCLASS()
class STEAKFRIES_API ACharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterSpawner();

public:
	APawn* SpawnCharacterPawn(const TSubclassOf<APawn>& PawnClass, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

protected:
	virtual void BeginPlay() override;

};
