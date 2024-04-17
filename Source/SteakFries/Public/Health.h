// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Damageable.h"
#include "Health.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, UObject*, DeadObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFullHeal, UObject*, HealedObject);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UHealth : public UActorComponent, public IDamageable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

	UPROPERTY(BlueprintAssignable)
	FOnFullHeal OnFullHeal;

	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;

protected:

	float MaxHealth = 100.0f;

	float CurrentHealth = 0.0f;

public:

	UFUNCTION(BlueprintCallable)
	virtual void DealFlatDamage(float damageAmount) override;

	UFUNCTION(BlueprintCallable)
	virtual void DealPercentageDamage(float damageAmount) override;

	UFUNCTION(BlueprintCallable)
	void HealFlatHealth(float healAmount);

	UFUNCTION(BlueprintCallable)
	void HealPercentageHealth(float healAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckDead();

};
