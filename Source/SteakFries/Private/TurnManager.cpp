// All rights reserved


#include "TurnManager.h"
#include "PaperFlipbookComponent.h"
#include "EnemyController.h"


void ATurnManager::Initialize(TArray<APawn*> Controllers)
{
	for (APawn* Controller : Controllers)
	{
		check(IsValid(Controller));

		TrySetInput(Controller, false);

		TurnQueue.Enqueue(Controller);
	}
}

void ATurnManager::Start()
{
	NextTurn();
}

void ATurnManager::NextTurn()
{
	// Dequeue
	check(TurnQueue.Dequeue(CurrentTurn));
	check(IsValid(CurrentTurn));

	TrySetInput(CurrentTurn, true);

	AEnemyController* EnemyController = nullptr;
	if (TryGetEnemyController(CurrentTurn->GetController(), EnemyController))
	{
		
	}


	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurn->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);
	}
}

void ATurnManager::EndTurn()
{
	check(IsValid(CurrentTurn));

	TrySetInput(CurrentTurn, false);

	TurnQueue.Enqueue(CurrentTurn);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurn->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);
	}

	NextTurn();
}

void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
}

bool ATurnManager::TrySetInput(APawn* Pawn, bool enable)
{
	APlayerController* PlayerController = nullptr;
	if (!TryGetPlayerController(Pawn->GetController(), PlayerController))
	{
		return false;
	}

	if (enable)
	{
		Pawn->EnableInput(PlayerController);
	}
	else
	{
		Pawn->DisableInput(PlayerController);
	}
	return true;
}

bool ATurnManager::TryGetPlayerController(AController* Controller, APlayerController*& OutPlayerController)
{
	OutPlayerController = nullptr;

	check(IsValid(Controller));
	if (!Controller->IsA(APlayerController::StaticClass()))
	{
		return false;
	}

	OutPlayerController = Cast<APlayerController>(Controller);
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
