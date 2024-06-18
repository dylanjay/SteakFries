// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionScriptPlayerComponent.generated.h"

class AAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScriptComplete);


UCLASS( BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UActionScriptPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnScriptComplete OnScriptComplete;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayScript(const TArray<AAction*> &Script);

};
