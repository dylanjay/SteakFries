// All rights reserved


#include "CharacterSpawner.h"
#include "BattleCharacter.h"


template <typename T>
T* ACharacterSpawner::Spawn(const TSubclassOf<ABattleCharacter>& Class, const FVector& Location, const FRotator& Rotation)
{
	T* Character = GetWorld()->SpawnActor<T>(Class, Location, Rotation);
	
	return Character;
}

void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

