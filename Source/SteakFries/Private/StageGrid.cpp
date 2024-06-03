// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGrid.h"
#include "StageCell.h"
#include "GridMovementComponent.h"


bool AStageGrid::CanMoveX(AStageCell* FromCell, int X) const
{
	if (X == 0)
	{
		return true;
	}

	UE::Math::TIntPoint<int> CurrentPoint = FromCell->GetGridPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return false;
	}

	int Direction = X > 0 ? 1 : -1;
	UE::Math::TIntPoint<int> NextCellPoint = CurrentPoint;
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

bool AStageGrid::CanMoveY(AStageCell* FromCell, int Y) const
{
	if (Y == 0)
	{
		return true;
	}

	UE::Math::TIntPoint<int> CurrentPoint = FromCell->GetGridPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y ))
	{
		return false;
	}

	int Direction = Y > 0 ? 1 : -1;
	UE::Math::TIntPoint<int> NextCellPoint = CurrentPoint;
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

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int X)
{
	if (X == 0)
	{
		return FromCell;
	}

	UE::Math::TIntPoint<int> CurrentPoint = FromCell->GetGridPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return FromCell;
	}

	int Direction = X > 0 ? 1 : -1;
	UE::Math::TIntPoint<int> NextPoint = CurrentPoint;
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

AStageCell* AStageGrid::TryMoveY(AStageCell* FromCell, int Y)
{
	if (Y == 0)
	{
		return FromCell;
	}

	UE::Math::TIntPoint<int> CurrentPoint = FromCell->GetGridPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y))
	{
		return FromCell;
	}

	int Direction = Y > 0 ? 1 : -1;
	UE::Math::TIntPoint<int> NextPoint = CurrentPoint;
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

bool AStageGrid::IsValidPoint(const TArray<int>& PointArray) const
{
	UE::Math::TIntPoint<int> Point(PointArray[0], PointArray[1]);
	return IsValidPoint(Point);
} 

bool AStageGrid::IsValidPoint(const UE::Math::TIntPoint<int>& Point) const
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

AStageCell* AStageGrid::GetNeighbor(AStageCell* Cell, EGridDirection Direction) const
{
	check(IsValid(Cell));
	
	return Cell;

	/*UE::Math::TIntPoint<int> NeighborPoint = Cell->GetGridPoint();
	switch (Direction)
	{
	case EGridDirection::UP:
		break;
	}*/
}

AStageCell* AStageGrid::GetCell(const TArray<int>& PointArray) const
{
	UE::Math::TIntPoint<int> Point(PointArray[0], PointArray[1]);
	return GetCell(Point);
}

AStageCell* AStageGrid::GetCell(const UE::Math::TIntPoint<int>& Point) const
{
	if (Point.X >= 0 && Point.X < Width && Point.Y >= 0 && Point.Y < Height)
	{
		AStageCell* Cell = Grid[Point.X][Point.Y];
		check(IsValid(Cell));
		return Cell;
	}
	return nullptr;
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, const UE::Math::TIntPoint<int>& StartingPoint)
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

	for (int colIndex = 0; colIndex < Width; colIndex++)
	{
		CellPoint.X = OriginCellX;

		TArray<AStageCell*> Col;

		for (int rowIndex = 0; rowIndex < Width; rowIndex++)
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

