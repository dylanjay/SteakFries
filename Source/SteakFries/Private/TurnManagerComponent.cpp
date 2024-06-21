// All rights reserved


#include "TurnManagerComponent.h"
#include "PaperFlipbookComponent.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BattleCharacter.h"
#include "BattleGameState.h"
#include "CharacterManagerComponent.h"
#include "CharacterTypes.h"
#include "PlayerControllerBase.h"


void UTurnManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	Start();
}

void UTurnManagerComponent::Initialize()
{
	PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());
	check(IsValid(PlayerController));

	ABattleGameState* BattleGameState = GetWorld()->GetGameState<ABattleGameState>();

	CharacterManager = BattleGameState->GetComponentByClass<UCharacterManagerComponent>();
	check(IsValid(CharacterManager));
}

void UTurnManagerComponent::Start()
{
	TrySetState(ETurnManagerState::FillingTurnQueue);
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

		EnemyController->GetEnemy()->OnStateEnterDelegate.AddUniqueDynamic(this, &UTurnManagerComponent::OnEnemyStateEnter);

		return;
	}

	TrySetStateNextTick(ETurnManagerState::TurnCycle);
}

void UTurnManagerComponent::NextTurn()
{
	TurnQueue.Dequeue(CurrentTurnCharacter);

	check(IsValid(CurrentTurnCharacter));

	switch (CurrentTurnCharacter->GetTeam())
	{
	case ETeam::Player:
	{
		PlayerController->Possess(CurrentTurnCharacter);
	}
	break;

	case ETeam::Enemy:
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(CurrentTurnCharacter->GetController());
		check(IsValid(EnemyController));

		EnemyController->ExecuteTurn();

	}
	break;
	}

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnCharacter->GetComponentByClass<UPaperFlipbookComponent>();
	PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);
}

void UTurnManagerComponent::FillTurnQueue()
{
	for (ABattleCharacter* Character : CharacterManager->GetAllCharacters())
	{
		check(IsValid(Character));

		TurnQueue.Enqueue(Character);
	}
	check(!TurnQueue.IsEmpty());

	TrySetStateNextTick(ETurnManagerState::SetEnemyIntentions);
}

void UTurnManagerComponent::EndTurn()
{
	check(IsValid(CurrentTurnCharacter));

	switch (CurrentTurnCharacter->GetTeam())
	{
	case ETeam::Player:
	{
		PlayerController->UnPossess();
	}
		break;
	}

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnCharacter->GetComponentByClass<UPaperFlipbookComponent>();
	PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);

	if (TurnQueue.IsEmpty())
	{
		TrySetStateNextTick(ETurnManagerState::FillingTurnQueue);
	}
	else
	{
		NextTurn();
	}
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
	case ETurnManagerState::FillingTurnQueue:
		FillTurnQueue();
		break;
	case ETurnManagerState::SetEnemyIntentions:
		SetEnemyIntentions();
		break;
	case ETurnManagerState::TurnCycle:
		NextTurn();
		break;
	}

	return true;
}

bool UTurnManagerComponent::TrySetStateNextTick(ETurnManagerState NewState)
{
	if (State == NewState)
	{
		return false;
	}

	GetWorld()->GetTimerManager().SetTimerForNextTick([this, NewState]()
		{
			TrySetState(NewState);
		});

	return true;
}

void UTurnManagerComponent::OnEnemyStateEnter(AEnemy* Enemy, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::IntentionSet:

		UPaperFlipbookComponent* PaperFlipbookComponent = Enemy->GetComponentByClass<UPaperFlipbookComponent>();
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);

		Enemy->OnStateEnterDelegate.RemoveDynamic(this, &UTurnManagerComponent::OnEnemyStateEnter);

		SetEnemyIntentions();

		break;
	}
}
