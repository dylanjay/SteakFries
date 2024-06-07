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
	TurnQueue.Dequeue(CurrentTurnPawn);

	check(IsValid(CurrentTurnPawn));

	TrySetInput(CurrentTurnPawn, true);

	AEnemyController* EnemyController = nullptr;

	bool IsPlayerTurn = !TryGetEnemyController(CurrentTurnPawn->GetController(), EnemyController);
	
	if (IsPlayerTurn)
	{
		TrySetInput(CurrentTurnPawn, true);
	}
	else
	{
		check(IsValid(EnemyController));
		
		EnemyController->MoveInRange();
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

	TrySetInput(CurrentTurnPawn, false);

	TurnQueue.Enqueue(CurrentTurnPawn);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurnPawn->GetComponentByClass<UPaperFlipbookComponent>();

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
