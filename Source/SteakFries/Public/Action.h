// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActionComplete);


UCLASS(Blueprintable, BlueprintType)
class STEAKFRIES_API UAction : public UObject
{
	GENERATED_BODY()
	
public:

	float Cost = 1.0f;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void DoAction(APawn* Pawn);

	FOnActionComplete OnActionCompleteDelegate;

};
