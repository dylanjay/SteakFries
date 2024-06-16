// All rights reserved

#pragma once

#include "PathFinding2D.h"

#define TPoint UE::Math::TIntPoint<int32>

template<IsPathFindable T>
class STEAKFRIES_API CardinalPathFinding : public PathFinding2D<T>
{
protected:

  TArray<const TPoint*> CardinalDirections;

public:

  CardinalPathFinding();

  virtual ~CardinalPathFinding();

  virtual TArray<const TPoint*> GetSearchPoints() override;

protected:

  virtual float CalculateHeuristicCost(T* Start, T* Destination) override;

};