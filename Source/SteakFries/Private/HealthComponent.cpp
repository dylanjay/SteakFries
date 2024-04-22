// All rights reserved


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	CurrentHealth = MaxHealth;
}


void UHealthComponent::DealFlatDamage(float damageAmount)
{
	CurrentHealth -= damageAmount;

	CheckDead();
}

void UHealthComponent::DealPercentageDamage(float damageAmount)
{
	DealFlatDamage(MaxHealth * damageAmount);
}

void UHealthComponent::HealFlatHealth(float healAmount)
{
	CurrentHealth = std::clamp(CurrentHealth + healAmount, 0.0f, MaxHealth);

	if (OnFullHeal.IsBound() && CurrentHealth == MaxHealth)
	{
		OnFullHeal.Broadcast(GetOwner());
	}
}

void UHealthComponent::HealPercentageHealth(float healAmount)
{
	HealFlatHealth(MaxHealth * healAmount);
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHealthComponent::CheckDead()
{
	if (OnDeath.IsBound() && CurrentHealth <= 0.0f)
	{
		OnDeath.Broadcast(GetOwner());
	}
}
