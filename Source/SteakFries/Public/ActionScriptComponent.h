// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionScriptComponent.generated.h"

class AAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScriptComplete);


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionScriptComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnScriptComplete OnScriptComplete;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayScript(const TArray<AAction*> &Script);

protected:
	virtual void BeginPlay() override;
};
