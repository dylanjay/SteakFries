// All rights reserved


#include "CharacterSpawner.h"

APawn* ACharacterSpawner::SpawnCharacterPawn(const TSubclassOf<APawn>& PawnClass, const FVector& Location, const FRotator& Rotation)
{
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(PawnClass, Location, Rotation);
	
	return Pawn;
}

void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

