// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

// Forward Declarations
class AController;


UCLASS()
class STEAKFRIES_API ATurnManager : public AActor
{
	GENERATED_BODY()

public:

	TQueue<AController*> TurnQueue;
	
public:	

	ATurnManager();

	void Initialize(TArray<AController*> Controllers);

	void Start();

	bool NextTurn();

	bool EndTurn();
	
protected:

	virtual void BeginPlay() override;

	bool TrySetInput(AController* Controller, bool enable);

protected:

	AController* CurrentTurn = nullptr;

};
