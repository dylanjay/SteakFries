// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionComplete);


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API AAction : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	float Cost = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	float Delay = 1.0f;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnActionComplete OnActionCompleteDelegate;

	UPROPERTY(BlueprintReadOnly)
	AGameModeBase* GameMode = nullptr;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void Initialize();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoAction(APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	float GetDelay() const { return Delay; }
};
