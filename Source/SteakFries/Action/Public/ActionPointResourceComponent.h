// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionPointResourceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionPointResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	float Get() const { return CurrentActionPoints; }

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable)
	bool CanAfford(float Amount) const { return CurrentActionPoints >= Amount;  }

	UFUNCTION(BlueprintCallable)
	bool TryConsume(float Amount);

	UFUNCTION(BlueprintCallable)
	void Refund(float Amount);

public:	
	UActionPointResourceComponent();

protected:

	virtual void BeginPlay() override;

protected:

	float MaxActionPoints = 10.0f;

	float CurrentActionPoints = 10.0f;
};
