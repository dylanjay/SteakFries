// All rights reserved


#include "CharacterSpawner.h"

ACharacterSpawner::ACharacterSpawner()
{

}

APawn* ACharacterSpawner::SpawnPlayerPawn()
{
	APawn* PlayerPawn = GetWorld()->SpawnActor<APawn>(PlayerPawnClass, GetActorLocation(), GetActorRotation());

	if (IsValid(PlayerPawn) && OnPlayerPawnSpawned.IsBound())
	{
		OnPlayerPawnSpawned.Broadcast(PlayerPawn);
	}
	
	return PlayerPawn;
}

void ACharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
}

