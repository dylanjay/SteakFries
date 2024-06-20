// All rights reserved


#include "PathFinding2D.h"


template<IsPathFindable T>
bool PathFinding2D<T>::TryFindPath(const TArray<TArray<T*>>& Grid, T* Start, T* Destination, TArray<T*>& OutPath)
{
	check(Start != nullptr);
	check(Destination != nullptr);
	check(Grid.Num() > 0);
	check(Grid[0].Num() > 0);

	if (Destination->IsBlocked())
	{
		return false;
	}

	if (Start == Destination)
	{
		return true;
	}

	int32 Width = Grid.Num();
	int32 Height = Grid[0].Num();

	TArray<TArray<SearchData>> DataMatrix;
	for (int32 ColIndex = 0; ColIndex < Width; ColIndex++)
	{
		TArray<SearchData> Col;

		for (int32 RowIndex = 0; RowIndex < Height; RowIndex++)
		{
			T* Node = Grid[ColIndex][RowIndex];
			SearchData SearchData(Node);
			Col.Add(SearchData);
		}

		DataMatrix.Add(Col);
	}

	SearchData& StartData = DataMatrix[Start->GetX()][Start->GetY()];
	StartData.Parent = Start;
	StartData.Cost = 0.0f;
	StartData.MoveCost = 0.0f;
	StartData.HeuristicCost = 0.0f;

	std::set<SearchData, decltype(&SearchData::Compare)> OpenList(&SearchData::Compare);

	OpenList.insert(StartData);

	while (OpenList.size() > 0)
	{
		const SearchData& Cur = *OpenList.begin();
		OpenList.erase(OpenList.begin());

		DataMatrix[Cur.Node->GetX()][Cur.Node->GetY()].Visited = true;

		for (const TPoint& SearchPoint : GetSearchPoints())
		{
			TPoint NeighborPoint = Cur.Node->GetPoint() + SearchPoint;

			if (IsValidPoint(NeighborPoint, Width, Height))
			{
				SearchData& Neighbor = DataMatrix[NeighborPoint.X][NeighborPoint.Y];

				// found destination
				if (Neighbor.Node == Destination)
				{
					Neighbor.Parent = Cur.Node;

					OutPath = TracePath(DataMatrix, Start, Destination);

					return true;
				}

				if (!Neighbor.Visited && !Neighbor.Node->IsBlocked())
				{
					float MoveCostNew = Cur.MoveCost + 1.0f;
					float HeuristicCostNew = CalculateHeuristicCost(Neighbor.Node, Destination);
					float CostNew = MoveCostNew + HeuristicCostNew;

					if (Neighbor.Cost == FLT_MAX
						|| Neighbor.Cost > CostNew)
					{
						Neighbor.Parent = Cur.Node;
						Neighbor.MoveCost = MoveCostNew;
						Neighbor.HeuristicCost = HeuristicCostNew;
						Neighbor.Cost = CostNew;
						OpenList.insert(Neighbor);
					}
				}
			}
		}
	}

	return false;
}

template<IsPathFindable T>
TArray<T*> PathFinding2D<T>::TracePath(const TArray<TArray<SearchData>>& DataMatrix, T* Start, T* Destination)
{
	TArray<T*> Path;

	T* Cur = Destination;

	std::stack<T*> Stack;

	while (DataMatrix[Cur->GetX()][Cur->GetY()].Node != Start)
	{
		check(Cur != nullptr);

		Stack.push(Cur);
		Cur = DataMatrix[Cur->GetX()][Cur->GetY()].Parent;
	}

	Path.Add(Cur);
	while (Stack.size() > 0)
	{
		Path.Add(Stack.top());
		Stack.pop();
	}

	return Path;
}

template<IsPathFindable T>
bool PathFinding2D<T>::IsValidPoint(TPoint Point, int32 Width, int32 Height)
{
	return Point.X >= 0 && Point.Y >= 0 && Point.X < Width && Point.Y < Height;
}