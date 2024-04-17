// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attack.generated.h"

UCLASS()
class STEAKFRIES_API AAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
