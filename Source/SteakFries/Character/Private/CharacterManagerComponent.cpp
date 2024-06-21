// All Rights Reserved

#include "CharacterManagerComponent.h"
#include "CharacterSpawnManagerComponent.h"
#include "BattleGameMode.h"
#include "BattleCharacter.h"
#include "CharacterTypes.h"
#include "PlayerBattleCharacter.h"
#include "Enemy.h"

void UCharacterManagerComponent::Initialize()
{
	ABattleGameMode* BattleGameMode = Cast<ABattleGameMode>(GetWorld()->GetAuthGameMode());

	UCharacterSpawnManagerComponent* CharacterSpawnManager = BattleGameMode->GetCharacterSpawnManager();
	check(IsValid(CharacterSpawnManager));

	CharacterSpawnManager->OnCharacterSpawnedDelegate.AddUniqueDynamic(this, &UCharacterManagerComponent::OnCharacterSpawned);
}

void UCharacterManagerComponent::OnCharacterSpawned(ABattleCharacter* Character)
{
	AllCharacters.Add(Character);

	switch (Character->GetTeam())
	{
	case ETeam::Player:
	{
		APlayerBattleCharacter* PlayerBattleCharacter = CastChecked<APlayerBattleCharacter>(Character);

		PlayerCharacters.Add(PlayerBattleCharacter);
	}
	break;

	case ETeam::Enemy:
	{
		AEnemy* Enemy = CastChecked<AEnemy>(Character);

		Enemies.Add(Enemy);
	}
	break;

	}
}
