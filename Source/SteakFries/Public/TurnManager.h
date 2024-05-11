// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

class AEnemyController;


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	

	void Initialize(TArray<APawn*> APawn);

	void Start();

	void NextTurn();

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void EndTurn();

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	bool TrySetInput(APawn* Pawn, bool enable);

	UFUNCTION(BlueprintCallable)
	bool TryGetPlayerController(AController* Controller, APlayerController*& OutPlayerController);

	UFUNCTION(BlueprintCallable)
	bool TryGetEnemyController(AController* Controller, AEnemyController*& OutEnemyController);

protected:

	virtual void BeginPlay() override;

protected:

	TQueue<APawn*> TurnQueue;

	APawn* CurrentTurn = nullptr;
};
