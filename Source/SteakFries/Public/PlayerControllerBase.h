// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"


UENUM(BlueprintType)
enum class EPlayerControllerState : uint8
{
	Default UMETA(DisplayName = "Default"),
	Movement UMETA(DisplayName = "Movement"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerControllerStateChange, EPlayerControllerState, NewState);

UCLASS()
class STEAKFRIES_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnPlayerControllerStateChange OnStateChangeDelegate;
	
protected:

	EPlayerControllerState State = EPlayerControllerState::Default;

public:

	UFUNCTION(BlueprintCallable)
	EPlayerControllerState GetState() const { return State; }

	UFUNCTION(BlueprintCallable)
	bool SetState(EPlayerControllerState NewState);

};