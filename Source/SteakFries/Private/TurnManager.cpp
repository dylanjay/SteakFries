// All rights reserved


#include "TurnManager.h"
#include "PaperFlipbookComponent.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BattleCharacter.h"
#include "BattleGameState.h"


void ATurnManager::Initialize(TArray<ABattleCharacter*> AllCharacters)
{
	for (ABattleCharacter* Character : AllCharacters)
	{
		check(IsValid(Character));

		TurnQueue.Enqueue(Character);
	}
}

void ATurnManager::Start()
{
	TrySetState(ETurnManagerState::SetEnemyIntentions);
}

void ATurnManager::SetEnemyIntentions()
{
	ABattleGameState* GameState = GetWorld()->GetAuthGameMode()->GetGameState<ABattleGameState>();

	TArray<AEnemy*> Enemies = GameState->GetEnemies();

	for (AEnemy* Enemy : Enemies)
	{
		if (Enemy->GetState() >= EEnemyState::SettingIntention)
		{
			continue;
		}

		UPaperFlipbookComponent* PaperFlipbookComponent = Enemy->GetComponentByClass<UPaperFlipbookComponent>();
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);

		AEnemyController* EnemyController = Cast<AEnemyController>(Enemy->GetController());

		EnemyController->SetIntention();

		return;
	}

	TrySetState(ETurnManagerState::TurnCycle);
}

void ATurnManager::NextTurn()
{
	TurnQueue.Dequeue(CurrentTurnCharacter);

	check(IsValid(CurrentTurnCharacter));

	AEnemyController* EnemyController = nullptr;
	if (TryGetEnemyController(CurrentTurnCharacter->GetController(), EnemyController))
	{
		EnemyController->ExecuteTurn();
	}

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnCharacter->GetComponentByClass<UPaperFlipbookComponent>();
	PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);
}

void ATurnManager::EndTurn()
{
	check(IsValid(CurrentTurnCharacter));

	TurnQueue.Enqueue(CurrentTurnCharacter);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnCharacter->GetComponentByClass<UPaperFlipbookComponent>();
	PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);

	NextTurn();
}

bool ATurnManager::TrySetState(ETurnManagerState NewState)
{
	if (State == NewState)
	{
		return false;
	}
	
	State = NewState;

	switch (State)
	{
	case ETurnManagerState::SetEnemyIntentions:
		SetEnemyIntentions();
		break;
	case ETurnManagerState::TurnCycle:
		NextTurn();
		break;
	}

	return true;
}

void ATurnManager::OnEnemyStateEnter(AEnemy* Enemy, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::IntentionSet:

		UPaperFlipbookComponent* PaperFlipbookComponent = Enemy->GetComponentByClass<UPaperFlipbookComponent>();
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);

		SetEnemyIntentions();

		break;
	}
}

bool ATurnManager::TryGetEnemyController(AController* Controller, AEnemyController*& OutEnemyController)
{
	OutEnemyController = nullptr;

	check(IsValid(Controller));
	if (!Controller->IsA(AEnemyController::StaticClass()))
	{
		return false;
	}

	OutEnemyController = Cast<AEnemyController>(Controller);
	return true;
}
