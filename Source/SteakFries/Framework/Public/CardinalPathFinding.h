// All rights reserved

#pragma once

#include "PathFinding2D.h"

#define TPoint UE::Math::TIntPoint<int32>

template<IsPathFindable T>
class STEAKFRIES_API CardinalPathFinding : public PathFinding2D<T>
{

public:

  virtual TArray<TPoint> GetSearchPoints() override;

protected:

  virtual float CalculateHeuristicCost(T* Start, T* Destination) override;

};