#include "CardinalPathFinding.h"

template<IsPathFindable T>
TArray<TPoint> CardinalPathFinding<T>::GetSearchPoints()
{
	return CardinalDirections::Get();
}

template<IsPathFindable T>
float CardinalPathFinding<T>::CalculateHeuristicCost(T* Start, T* Destination)
{
	// Manhattan Distance
	TPoint StartPoint = Start->GetPoint();
	TPoint DestinationPoint = Destination->GetPoint();
	return std::abs(StartPoint.X - DestinationPoint.X) + std::abs(StartPoint.Y - DestinationPoint.Y);
}
