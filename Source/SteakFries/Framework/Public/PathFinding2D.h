// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "PathFindable2D.h"

#define TPoint UE::Math::TIntPoint<int32>

template<typename T>
concept PathFindable = std::is_base_of<IPathFindable2D, T>::value;

template<PathFindable T>
class STEAKFRIES_API PathFinding2D
{
protected:

	struct SearchData
	{
		T* Node = nullptr;
		T* Parent = nullptr;

		bool Visited = false;

		float Cost = FLT_MAX;
		float MoveCost = FLT_MAX;
		float HeuristicCost = FLT_MAX;

		SearchData(T* InNode)
		{
			Node = InNode;
		}

		static bool Compare(const SearchData& left, const SearchData& right)
		{
			return left.Cost <= right.Cost;
		}
	};

public:

	bool TryFindPath(const TArray<TArray<T*>>& Grid, T* Start, T* Destination, TArray<T*>& OutPath);

public:

	virtual TArray<const TPoint*> GetSearchPoints() = 0;

protected:

	virtual float CalculateHeuristicCost(T* Start, T* Destination) = 0;

protected:

	TArray<T*> TracePath(const TArray<TArray<SearchData>>& DataMatrix, T* Start, T* Destination);

	bool IsValidPoint(TPoint Point, int32 Width, int32 Height);
};
