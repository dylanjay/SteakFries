#include "CardinalPathFinding.h"

template<IsPathFindable T>
CardinalPathFinding<T>::CardinalPathFinding()
{
	CardinalDirections =
	{
		new UE::Math::TIntPoint<int32>(0, 1),
		new UE::Math::TIntPoint<int32>(1, 0),
		new UE::Math::TIntPoint<int32>(0, -1),
		new UE::Math::TIntPoint<int32>(-1, 0)
	};
}

template<IsPathFindable T>
CardinalPathFinding<T>::~CardinalPathFinding()
{
	for (int i = 0; i < CardinalDirections.Num(); i++)
	{
		delete(CardinalDirections[i]);
	}
}

template<IsPathFindable T>
TArray<const TPoint*> CardinalPathFinding<T>::GetSearchPoints()
{
	return CardinalDirections;
}

template<IsPathFindable T>
float CardinalPathFinding<T>::CalculateHeuristicCost(T* Start, T* Destination)
{
	// Manhattan Distance
	TPoint StartPoint = Start->GetPoint();
	TPoint DestinationPoint = Destination->GetPoint();
	return std::abs(StartPoint.X - DestinationPoint.X) + std::abs(StartPoint.Y - DestinationPoint.Y);
}
