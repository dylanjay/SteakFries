// All rights reserved


#include "CharacterSpawner.h"

ACharacterSpawner::ACharacterSpawner()
{

}

APawn* ACharacterSpawner::SpawnCharacterPawn(const TSubclassOf<APawn>& PawnClass, const TArray<int>& StartingLocation)
{
	APawn* Pawn = GetWorld()->SpawnActor<APawn>(PawnClass, GetActorLocation(), GetActorRotation());

	if (IsValid(Pawn))
	{
		OnCharacterPawnSpawned.Broadcast(Pawn, StartingLocation);
	}
	
	return Pawn;
}

void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

