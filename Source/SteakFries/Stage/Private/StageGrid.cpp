// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGrid.h"
#include "GridMovementComponent.h"
#include <stack>
#include <set>
#include "Logging/StructuredLog.h"


bool AStageGrid::CanMoveX(AStageCell* FromCell, int32 X) const
{
	if (X == 0)
	{
		return true;
	}

	UE::Math::TIntPoint<int32> CurrentPoint = FromCell->GetGridPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return false;
	}

	int32 Direction = X > 0 ? 1 : -1;
	UE::Math::TIntPoint<int32> NextCellPoint = CurrentPoint;
	NextCellPoint.X += Direction;
	AStageCell* NextCell = GetCell(NextCellPoint);

	while (X != 0)
	{
		if (NextCell->IsFilled())
		{
			return false;
		}

		X -= Direction;

		if (X == 0)
		{
			break;
		}

		CurrentPoint = NextCellPoint;
		NextCellPoint.X += Direction;
		NextCell = GetCell(NextCellPoint);
	}

	return !NextCell->IsFilled();
}

bool AStageGrid::CanMoveY(AStageCell* FromCell, int32 Y) const
{
	if (Y == 0)
	{
		return true;
	}

	UE::Math::TIntPoint<int32> CurrentPoint = FromCell->GetGridPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y ))
	{
		return false;
	}

	int32 Direction = Y > 0 ? 1 : -1;
	UE::Math::TIntPoint<int32> NextCellPoint = CurrentPoint;
	NextCellPoint.Y += Direction;
	AStageCell* NextCell = GetCell(NextCellPoint);

	while (Y != 0)
	{
		if (NextCell->IsFilled())
		{
			return false;
		}

		Y -= Direction;

		if (Y == 0)
		{
			break;
		}

		CurrentPoint = NextCellPoint;
		NextCellPoint.Y += Direction;
		NextCell = GetCell(NextCellPoint);
	}

	return !NextCell->IsFilled();
}

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int32 X)
{
	if (X == 0)
	{
		return FromCell;
	}

	UE::Math::TIntPoint<int32> CurrentPoint = FromCell->GetGridPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return FromCell;
	}

	int32 Direction = X > 0 ? 1 : -1;
	UE::Math::TIntPoint<int32> NextPoint = CurrentPoint;
	NextPoint.X += Direction;
	AStageCell* NextCell = GetCell(NextPoint);

	if (NextCell->IsFilled())
	{
		return FromCell;
	}

	while (X != 0 && NextPoint.X < Width && NextPoint.X >= 0 && !NextCell->IsFilled())
	{
		X -= Direction;
		CurrentPoint = NextPoint;
		NextPoint.X += Direction;
		NextCell = GetCell(NextPoint);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurrentPoint);
	CurCell->Fill(Actor);

	CharacterCells[Actor] = CurCell;

	return CurCell;
}

AStageCell* AStageGrid::TryMoveY(AStageCell* FromCell, int32 Y)
{
	if (Y == 0)
	{
		return FromCell;
	}

	UE::Math::TIntPoint<int32> CurrentPoint = FromCell->GetGridPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y))
	{
		return FromCell;
	}

	int32 Direction = Y > 0 ? 1 : -1;
	UE::Math::TIntPoint<int32> NextPoint = CurrentPoint;
	NextPoint.Y += Direction;
	AStageCell* NextCell = GetCell(NextPoint);

	if (NextCell->IsFilled())
	{
		return FromCell;
	}

	while (Y != 0 && NextPoint.Y < Height && NextPoint.Y >= 0 && !NextCell->IsFilled())
	{
		Y -= Direction;
		CurrentPoint = NextPoint;
		NextPoint.Y += Direction;
		NextCell = GetCell(NextPoint);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurrentPoint);
	CurCell->Fill(Actor);

	CharacterCells[Actor] = CurCell;

	return CurCell;
}

AStageCell* AStageGrid::FindCharacter(AActor* Actor) const
{
	if (!CharacterCells.Contains(Actor))
	{ 
		return nullptr;
	}
	
	return CharacterCells[Actor];
}

bool AStageGrid::IsValidPoint(const TArray<int32>& PointArray) const
{
	UE::Math::TIntPoint<int32> Point(PointArray[0], PointArray[1]);
	return IsValidPoint(Point);
} 

bool AStageGrid::IsValidPoint(const UE::Math::TIntPoint<int32>& Point) const
{
	if (Point.X < 0 || Point.X >= Width)
	{
		return false;
	}

	if (Point.Y < 0 || Point.Y >= Height)
	{
		return false;
	}

	return true;
}

bool AStageGrid::IsFilled(const UE::Math::TIntPoint<int32>& Point) const
{
	check(IsValidPoint(Point));

	return GetCell(Point)->IsFilled();
}

AStageCell* AStageGrid::GetCell(const TArray<int32>& PointArray) const
{
	check(PointArray.Num() >= 2);
	UE::Math::TIntPoint<int32> Point(PointArray[0], PointArray[1]);
	return GetCell(Point);
}

AStageGrid::AStageGrid()
{
	CardinalDirections =
	{
		new UE::Math::TIntPoint<int32>(0, 1),
		new UE::Math::TIntPoint<int32>(1, 0),
		new UE::Math::TIntPoint<int32>(0, -1),
		new UE::Math::TIntPoint<int32>(-1, 0)
	};
}

AStageCell* AStageGrid::GetCell(const UE::Math::TIntPoint<int32>& Point) const
{
	if (Point.X >= 0 && Point.X < Width && Point.Y >= 0 && Point.Y < Height)
	{
		AStageCell* Cell = Grid[Point.X][Point.Y];
		check(IsValid(Cell));
		return Cell;
	}
	return nullptr;
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, const UE::Math::TIntPoint<int32>& StartingPoint)
{
	if (!IsValid(Pawn))
	{
		return false;
	}

	UGridMovementComponent* GridMovementComp = Pawn->GetComponentByClass<UGridMovementComponent>();
	check(IsValid(GridMovementComp));

	AStageCell* StageCell = GetCell(StartingPoint);
	check(IsValid(StageCell));

	if (StageCell->IsFilled())
	{
		return false;
	}

	CharacterCells.Add(Pawn, StageCell);

	StageCell->Fill(Pawn);
	
	GridMovementComp->Initialize(this, StageCell);

	return true;
}

bool AStageGrid::TryFindPathToCell(AStageCell* Start, AStageCell* Destination, TArray<AStageCell*>& OutPath)
{
	check(IsValid(Start));
	check(IsValid(Destination));

	if (Destination->IsFilled())
	{
		return false;
	}

	if (Start == Destination)
	{
		return true;
	}

	TArray<TArray<CellSearchData>> DataMatrix;
	for (int32 ColIndex = 0; ColIndex < GetWidth(); ColIndex++)
	{
		TArray<CellSearchData> Col;

		TPoint Point;

		for (int32 RowIndex = 0; RowIndex < GetHeight(); RowIndex++)
		{
			Point.X = ColIndex;
			Point.Y = RowIndex;

			AStageCell* Cell = GetCell(Point);
			CellSearchData CellData(Cell);
			Col.Add(CellData);
		}

		DataMatrix.Add(Col);
	}

	TPoint StartPoint = Start->GetGridPoint();
	DataMatrix[StartPoint.X][StartPoint.Y].Parent = Start;
	DataMatrix[StartPoint.X][StartPoint.Y].Cost = 0.0f;
	DataMatrix[StartPoint.X][StartPoint.Y].MoveCost = 0.0f;
	DataMatrix[StartPoint.X][StartPoint.Y].HeuristicCost = 0.0f;

	std::set<CellSearchData, decltype(&CellSearchData::Compare)> OpenList(&CellSearchData::Compare);

	OpenList.insert(DataMatrix[StartPoint.X][StartPoint.Y]);

	while (OpenList.size() > 0)
	{
		const CellSearchData &Cur = *OpenList.begin();
		OpenList.erase(OpenList.begin());

		TPoint CurPoint = Cur.Cell->GetGridPoint();

		DataMatrix[CurPoint.X][CurPoint.Y].Visited = true;

		for (const TPoint* Direction : CardinalDirections)
		{
			TPoint NeighborPoint = CurPoint + *Direction;

			if (IsValidPoint(NeighborPoint))
			{
				const CellSearchData &Neighbor = DataMatrix[NeighborPoint.X][NeighborPoint.Y];

				// found destination
				if (Neighbor.Cell == Destination)
				{
					DataMatrix[NeighborPoint.X][NeighborPoint.Y].Parent = Cur.Cell;

					OutPath = TracePath(DataMatrix, Start, Destination);

					return true;
				}

				if (!Neighbor.Visited && !IsFilled(Neighbor.Cell->GetGridPoint()))
				{
					float MoveCostNew = DataMatrix[CurPoint.X][CurPoint.Y].MoveCost + 1.0f;
					float HeuristicCostNew = DataMatrix[NeighborPoint.X][NeighborPoint.Y].CalculateHeuristicCost(Destination);
					float CostNew = MoveCostNew + HeuristicCostNew;

					if (DataMatrix[NeighborPoint.X][NeighborPoint.Y].Cost == FLT_MAX
						|| DataMatrix[NeighborPoint.X][NeighborPoint.Y].Cost > CostNew)
					{
						DataMatrix[NeighborPoint.X][NeighborPoint.Y].Parent = Cur.Cell;
						DataMatrix[NeighborPoint.X][NeighborPoint.Y].MoveCost = MoveCostNew;
						DataMatrix[NeighborPoint.X][NeighborPoint.Y].HeuristicCost = HeuristicCostNew;
						DataMatrix[NeighborPoint.X][NeighborPoint.Y].Cost = CostNew;
						OpenList.insert(DataMatrix[NeighborPoint.X][NeighborPoint.Y]);
					}
				}
			}
		}
	}

	return false;
}

TArray<AStageCell*> AStageGrid::TracePath(const TArray<TArray<CellSearchData>>& DataMatrix, AStageCell* Start, AStageCell* Destination)
{
	TArray<AStageCell*> Path;

	AStageCell* Cur = Destination;
	TPoint CurPoint = Destination->GetGridPoint();

	std::stack<AStageCell*> Stack;

	while (DataMatrix[Cur->GetGridPoint().X][Cur->GetGridPoint().Y].Cell != Start)
	{
		Stack.push(Cur);
		Cur = DataMatrix[Cur->GetGridPoint().X][Cur->GetGridPoint().Y].Parent;
	}

	Path.Add(Cur);
	while (Stack.size() > 0)
	{
		Path.Add(Stack.top());
		Stack.pop();
	}

	return Path;
}

void AStageGrid::CreateGrid()
{
	FRotator Rotation = GetActorRotation();

	AStageCell* FirstCell = GetWorld()->SpawnActor<AStageCell>(StageCellClass, GetActorLocation(), Rotation);
	check(IsValid(FirstCell));

	float CellLength = FirstCell->GetLength();
	float CellWidth = FirstCell->GetWidth();

	FirstCell->SetActorRelativeLocation(FVector(-CellLength / 2.0f, CellWidth / 2.0f, 0.0f));

	FVector CellPoint = FirstCell->GetActorLocation();

	float OriginCellX = CellPoint.X;

	for (int32 colIndex = 0; colIndex < Width; colIndex++)
	{
		CellPoint.X = OriginCellX;

		TArray<AStageCell*> Col;

		for (int32 rowIndex = 0; rowIndex < Width; rowIndex++)
		{
			AStageCell* Cell;
			if (colIndex == 0 && rowIndex == 0)
			{
				Cell = FirstCell;
			}
			else
			{
				Cell = GetWorld()->SpawnActor<AStageCell>(StageCellClass, CellPoint, Rotation);
			}

			Cell->Initialize(colIndex, rowIndex);

			CellPoint.X += CellLength;

			Col.Add(Cell);
		}

		CellPoint.Y += CellWidth;

		Grid.Add(Col);
	}
}

void AStageGrid::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
}

