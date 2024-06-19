// All rights reserved


#include "CharacterSpawnManagerComponent.h"
#include "BattleCharacter.h"
#include "StageGridManagerComponent.h"
#include "BattleGameState.h"
#include "StageGrid.h"
#include "StageCell.h"

void UCharacterSpawnManagerComponent::Initialize()
{
	ABattleGameState* BattleGameState = GetWorld()->GetGameState<ABattleGameState>();

	StageGrid = BattleGameState->GetComponentByClass<UStageGridManagerComponent>()->GetStageGrid();
	check(IsValid(StageGrid));
}

template <typename T>
T* UCharacterSpawnManagerComponent::Spawn(
	const TSubclassOf<ABattleCharacter>& Class, 
	ETeam Team, 
	const TPoint& SpawnPoint, 
	const FRotator& Rotation)
{
	const FVector SpawnLocation = StageGrid->GetCell(SpawnPoint)->GetActorLocation();

	ABattleCharacter* BattleCharacter = GetWorld()->SpawnActor<ABattleCharacter>(Class, SpawnLocation, Rotation);

	StageGrid->InitializeOnGrid(BattleCharacter, SpawnPoint);

	BattleCharacter->Initialize(Team);

	OnCharacterSpawnedDelegate.Broadcast(BattleCharacter);

	T* DerivedCharacter = Cast<T>(BattleCharacter);
	
	return DerivedCharacter;
}