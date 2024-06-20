// All Rights Reserved

#pragma once

#include "CoreMinimal.h"

#define TPoint UE::Math::TIntPoint<int32>

class STEAKFRIES_API CardinalDirections
{
protected:

  static TArray<TPoint> Directions;

public:

  static TArray<TPoint> Get();

};