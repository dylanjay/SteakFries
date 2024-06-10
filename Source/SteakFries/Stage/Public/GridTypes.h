#pragma once

#include "CoreMinimal.h"
#include "GridTypes.generated.h"


UENUM(BlueprintType)
enum class EGridDirection : uint8
{
  UP UMETA(DisplayName = "UP"),
  DOWN UMETA(DisplayName = "DOWN"),
  LEFT UMETA(DisplayName = "LEFT"),
  RIGHT UMETA(DisplayName = "RIGHT"),
};