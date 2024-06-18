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

	template <typename T>
	T* Spawn(const TSubclassOf<ABattleCharacter>& Class, const FVector& Location, const FRotator& Rotation = FRotator::ZeroRotator);

protected:
	virtual void BeginPlay() override;

};
