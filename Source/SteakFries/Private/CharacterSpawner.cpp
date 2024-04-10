// All rights reserved


#include "CharacterSpawner.h"

ACharacterSpawner::ACharacterSpawner()
{

}

APawn* ACharacterSpawner::SpawnPlayerPawn(const TArray<int>& StartingLocation)
{
	APawn* PlayerPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, GetActorLocation(), GetActorRotation());

	if (IsValid(PlayerPawn))
	{
		OnCharacterPawnSpawned.Broadcast(PlayerPawn, StartingLocation);
	}
	
	return PlayerPawn;
}

void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

