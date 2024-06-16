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

	TPoint CurrentPoint = FromCell->GetPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return false;
	}

	int32 Direction = X > 0 ? 1 : -1;
	TPoint NextCellPoint = CurrentPoint;
	NextCellPoint.X += Direction;
	AStageCell* NextCell = GetCell(NextCellPoint);

	while (X != 0)
	{
		if (NextCell->IsBlocked())
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

	return !NextCell->IsBlocked();
}

bool AStageGrid::CanMoveY(AStageCell* FromCell, int32 Y) const
{
	if (Y == 0)
	{
		return true;
	}

	TPoint CurrentPoint = FromCell->GetPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y ))
	{
		return false;
	}

	int32 Direction = Y > 0 ? 1 : -1;
	TPoint NextCellPoint = CurrentPoint;
	NextCellPoint.Y += Direction;
	AStageCell* NextCell = GetCell(NextCellPoint);

	while (Y != 0)
	{
		if (NextCell->IsBlocked())
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

	return !NextCell->IsBlocked();
}

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int32 X)
{
	if (X == 0)
	{
		return FromCell;
	}

	TPoint CurrentPoint = FromCell->GetPoint();

	if ((X > 0 && CurrentPoint.X >= Width - X) ||
		(X < 0 && CurrentPoint.X < -X))
	{
		return FromCell;
	}

	int32 Direction = X > 0 ? 1 : -1;
	TPoint NextPoint = CurrentPoint;
	NextPoint.X += Direction;
	AStageCell* NextCell = GetCell(NextPoint);

	if (NextCell->IsBlocked())
	{
		return FromCell;
	}

	while (X != 0 && NextPoint.X < Width && NextPoint.X >= 0 && !NextCell->IsBlocked())
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

	TPoint CurrentPoint = FromCell->GetPoint();

	if ((Y > 0 && CurrentPoint.Y >= Height - Y) ||
		(Y < 0 && CurrentPoint.Y < -Y))
	{
		return FromCell;
	}

	int32 Direction = Y > 0 ? 1 : -1;
	TPoint NextPoint = CurrentPoint;
	NextPoint.Y += Direction;
	AStageCell* NextCell = GetCell(NextPoint);

	if (NextCell->IsBlocked())
	{
		return FromCell;
	}

	while (Y != 0 && NextPoint.Y < Height && NextPoint.Y >= 0 && !NextCell->IsBlocked())
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
	TPoint Point(PointArray[0], PointArray[1]);
	return IsValidPoint(Point);
} 

bool AStageGrid::IsValidPoint(const TPoint& Point) const
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

bool AStageGrid::IsBlocked(const TPoint& Point) const
{
	check(IsValidPoint(Point));

	return GetCell(Point)->IsBlocked();
}

TArray<const TPoint*> AStageGrid::GetCardinalDirections() const
{
	check(PathFinding != nullptr);
	return PathFinding->GetSearchPoints();
}

AStageCell* AStageGrid::GetCell(const TArray<int32>& PointArray) const
{
	check(PointArray.Num() >= 2);
	TPoint Point(PointArray[0], PointArray[1]);
	return GetCell(Point);
}

AStageGrid::AStageGrid()
{
	PathFinding = new CardinalPathFinding<AStageCell>();
}

AStageGrid::~AStageGrid()
{
	delete(PathFinding);
}

AStageCell* AStageGrid::GetCell(const TPoint& Point) const
{
	if (Point.X >= 0 && Point.X < Width && Point.Y >= 0 && Point.Y < Height)
	{
		AStageCell* Cell = Grid[Point.X][Point.Y];
		check(IsValid(Cell));
		return Cell;
	}
	return nullptr;
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, const TPoint& StartingPoint)
{
	if (!IsValid(Pawn))
	{
		return false;
	}

	UGridMovementComponent* GridMovementComp = Pawn->GetComponentByClass<UGridMovementComponent>();
	check(IsValid(GridMovementComp));

	AStageCell* StageCell = GetCell(StartingPoint);
	check(IsValid(StageCell));

	if (StageCell->IsBlocked())
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
	check(PathFinding != nullptr);

	return PathFinding->TryFindPath(Grid, Start, Destination, OutPath);
}

void AStageGrid::OnBeginCursorOverCell(AStageCell* Cell)
{
	check(IsValid(Cell));

	if (OnBeginCursorOverCellDelegate.IsBound())
	{
		OnBeginCursorOverCellDelegate.Broadcast(Cell);
	}
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

			Cell->Initialize(this, colIndex, rowIndex);

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

