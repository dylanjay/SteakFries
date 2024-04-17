// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"


UINTERFACE(MinimalAPI, NotBlueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STEAKFRIES_API IDamageable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual void DealFlatDamage(float damageAmount) = 0;

	UFUNCTION(BlueprintCallable)
	virtual void DealPercentageDamage(float damageAmount);

};
