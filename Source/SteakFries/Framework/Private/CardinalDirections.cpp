// All Rights Reserved

#include "CardinalDirections.h"

TArray<TPoint> CardinalDirections::Directions =
{
		TPoint(0, 1),
		TPoint(1, 0),
		TPoint(0, -1),
		TPoint(-1, 0),
};

TArray<TPoint> CardinalDirections::Get()
{
	return Directions;
}