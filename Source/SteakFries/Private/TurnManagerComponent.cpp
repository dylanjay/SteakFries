// All rights reserved


#include "TurnManagerComponent.h"
#include "PaperFlipbookComponent.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BattleCharacter.h"
#include "BattleGameState.h"
#include "CharacterManagerComponent.h"


void UTurnManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	Start();
}

void UTurnManagerComponent::Initialize()
{
	ABattleGameState* BattleGameState = GetWorld()->GetGameState<ABattleGameState>();

	CharacterManager = BattleGameState->GetComponentByClass<UCharacterManagerComponent>();
	check(IsValid(CharacterManager));

	for (ABattleCharacter* Character : CharacterManager->GetAllCharacters())
	{
		check(IsValid(Character));

		TurnQueue.Enqueue(Character);
	}
}

void UTurnManagerComponent::Start()
{
	TrySetState(ETurnManagerState::SetEnemyIntentions);
}

void UTurnManagerComponent::SetEnemyIntentions()
{
	TArray<AEnemy*> Enemies = CharacterManager->GetEnemies();

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

void UTurnManagerComponent::NextTurn()
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

void UTurnManagerComponent::EndTurn()
{
	check(IsValid(CurrentTurnCharacter));

	TurnQueue.Enqueue(CurrentTurnCharacter);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnCharacter->GetComponentByClass<UPaperFlipbookComponent>();
	PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);

	NextTurn();
}

bool UTurnManagerComponent::TrySetState(ETurnManagerState NewState)
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

void UTurnManagerComponent::OnEnemyStateEnter(AEnemy* Enemy, EEnemyState NewState)
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

bool UTurnManagerComponent::TryGetEnemyController(AController* Controller, AEnemyController*& OutEnemyController)
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
