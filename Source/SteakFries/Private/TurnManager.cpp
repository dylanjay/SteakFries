// All rights reserved


#include "TurnManager.h"
#include "PaperFlipbookComponent.h"


ATurnManager::ATurnManager()
{

}

void ATurnManager::Initialize(TArray<AController*> Controllers)
{
	for (AController* Controller : Controllers)
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

bool ATurnManager::NextTurn()
{
	// Dequeue
	check(TurnQueue.Dequeue(CurrentTurn));
	check(IsValid(CurrentTurn));

	APawn* Pawn = CurrentTurn->GetPawn();

	UPaperFlipbookComponent* PaperFlipbookComponent = Pawn->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::Red);
	}

	return true;
}

bool ATurnManager::EndTurn()
{
	if (CurrentTurn == nullptr)
	{
		return false;
	}

	TrySetInput(CurrentTurn, false);

	TurnQueue.Enqueue(CurrentTurn);

	UPaperFlipbookComponent* PaperFlipbookComponent = CurrentTurn->GetPawn()->GetComponentByClass<UPaperFlipbookComponent>();

	if (PaperFlipbookComponent)
	{
		PaperFlipbookComponent->SetSpriteColor(FLinearColor::White);
	}

	return NextTurn();
}

void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
}

bool ATurnManager::TrySetInput(AController* Controller, bool enable)
{
	if (!Controller->IsA(APlayerController::StaticClass()))
	{
		return false;
	}

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (enable)
	{
		PlayerController->EnableInput(PlayerController);
	}
	else
	{
		PlayerController->DisableInput(PlayerController);
	}
	return true;
}
