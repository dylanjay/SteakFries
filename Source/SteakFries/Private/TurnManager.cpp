// All rights reserved


#include "TurnManager.h"
#include "PaperFlipbookComponent.h"
#include "EnemyController.h"
#include "Enemy.h"


void ATurnManager::Initialize(TArray<APawn*> Pawns)
{
	for (APawn* Pawn : Pawns)
	{
		check(IsValid(Pawn));

		TurnQueue.Enqueue(Pawn);

		AEnemyController* EnemyController = nullptr;

		if (TryGetEnemyController(CurrentTurnPawn->GetController(), EnemyController))
		{
			EnemyControllers.Add(EnemyController);

			// On Enemy Intention Set
		}
	}
}

void ATurnManager::Start()
{
	TrySetState(ETurnManagerState::SetEnemyIntentions);
}

void ATurnManager::SetEnemyIntentions()
{
	for (AEnemyController* EnemyController : EnemyControllers)
	{
		if (EnemyController->GetEnemy()->GetState() >= EEnemyState::SettingIntention)
		{
			continue;
		}

		EnemyController->SetIntention();

		return;
	}

	TrySetState(ETurnManagerState::TurnCycle);
}

void ATurnManager::NextTurn()
{
	TurnQueue.Dequeue(CurrentTurnPawn);

	check(IsValid(CurrentTurnPawn));

	AEnemyController* EnemyController = nullptr;
	if (TryGetEnemyController(CurrentTurnPawn->GetController(), EnemyController))
	{
		EnemyController->ExecuteTurn();
	}

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnPawn->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);
	}
}

void ATurnManager::EndTurn()
{
	check(IsValid(CurrentTurnPawn));

	TurnQueue.Enqueue(CurrentTurnPawn);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnPawn->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);
	}

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
