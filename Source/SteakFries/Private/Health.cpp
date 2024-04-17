#include "Health.h"
// All rights reserved


#include "Health.h"

UHealth::UHealth()
{
	CurrentHealth = MaxHealth;
}


void UHealth::DealFlatDamage(float damageAmount)
{
	CurrentHealth -= damageAmount;

	CheckDead();
}

void UHealth::DealPercentageDamage(float damageAmount)
{
	DealFlatDamage(MaxHealth * damageAmount);
}

void UHealth::HealFlatHealth(float healAmount)
{
	CurrentHealth = std::clamp(CurrentHealth + healAmount, 0.0f, MaxHealth);

	if (OnFullHeal.IsBound() && CurrentHealth == MaxHealth)
	{
		OnFullHeal.Broadcast(GetOwner());
	}
}

void UHealth::HealPercentageHealth(float healAmount)
{
	HealFlatHealth(MaxHealth * healAmount);
}


void UHealth::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHealth::CheckDead()
{
	if (OnDeath.IsBound() && CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast(GetOwner());
	}
}
