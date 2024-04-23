// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGrid.h"
#include "StageCell.h"
#include "GridMovementComponent.h"

AStageGrid::AStageGrid()
{

}

bool AStageGrid::CanMoveX(AStageCell* FromCell, int X)
{
	if (X == 0)
	{
		return true;
	}

	TArray<int> CurrentLocation = FromCell->GetGridLocation();

	if ((X > 0 && CurrentLocation[0] >= Width - X) ||
		(X < 0 && CurrentLocation[0] < -X))
	{
		return false;
	}

	int Direction = X > 0 ? 1 : -1;
	TArray<int> NextCellLocation = CurrentLocation;
	NextCellLocation[0] += Direction;
	AStageCell* NextCell = GetCell(NextCellLocation);

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

		CurrentLocation = NextCellLocation;
		NextCellLocation[0] += Direction;
		NextCell = GetCell(NextCellLocation);
	}

	return !NextCell->IsFilled();
}

bool AStageGrid::CanMoveY(AStageCell* FromCell, int Y)
{
	if (Y == 0)
	{
		return true;
	}

	TArray<int> CurrentLocation = FromCell->GetGridLocation();

	if ((Y > 0 && CurrentLocation[1] >= Height - Y) ||
		(Y < 0 && CurrentLocation[1] < -Y ))
	{
		return false;
	}

	int Direction = Y > 0 ? 1 : -1;
	TArray<int> NextCellLocation = CurrentLocation;
	NextCellLocation[1] += Direction;
	AStageCell* NextCell = GetCell(NextCellLocation);

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

		CurrentLocation = NextCellLocation;
		NextCellLocation[1] += Direction;
		NextCell = GetCell(NextCellLocation);
	}

	return !NextCell->IsFilled();
}

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int X)
{
	if (X == 0)
	{
		return FromCell;
	}

	TArray<int> CurrentLocation = FromCell->GetGridLocation();

	if ((X > 0 && CurrentLocation[0] >= Width - X) ||
		(X < 0 && CurrentLocation[0] < -X))
	{
		return FromCell;
	}

	int Direction = X > 0 ? 1 : -1;
	TArray<int> NextLocation = CurrentLocation;
	NextLocation[0] += Direction;
	AStageCell* NextCell = GetCell(NextLocation);

	if (NextCell->IsFilled())
	{
		return FromCell;
	}

	while (X != 0 && NextLocation[0] < Width && NextLocation[0] >= 0 && !NextCell->IsFilled())
	{
		X -= Direction;
		CurrentLocation = NextLocation;
		NextLocation[0] += Direction;
		NextCell = GetCell(NextLocation);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurrentLocation);
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

	TArray<int> CurrentLocation = FromCell->GetGridLocation();

	if ((Y > 0 && CurrentLocation[1] >= Height - Y) ||
		(Y < 0 && CurrentLocation[1] < -Y))
	{
		return FromCell;
	}

	int Direction = Y > 0 ? 1 : -1;
	TArray<int> NextLocation = CurrentLocation;
	NextLocation[1] += Direction;
	AStageCell* NextCell = GetCell(NextLocation);

	if (NextCell->IsFilled())
	{
		return FromCell;
	}

	while (Y != 0 && NextLocation[1] < Height && NextLocation[1] >= 0 && !NextCell->IsFilled())
	{
		Y -= Direction;
		CurrentLocation = NextLocation;
		NextLocation[1] += Direction;
		NextCell = GetCell(NextLocation);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurrentLocation);
	CurCell->Fill(Actor);

	CharacterCells[Actor] = CurCell;

	return CurCell;
}

AStageCell* AStageGrid::FindCharacter(AActor* Actor)
{
	if (!CharacterCells.Contains(Actor))
	{ 
		return nullptr;
	}
	
	return CharacterCells[Actor];
}

AStageCell* AStageGrid::GetCell(const TArray<int>& Location)
{
	if (Location[0] >= 0 && Location[0] < Width && Location[1] >= 0 && Location[1] < Height)
	{
		return Grid[Location[0]][Location[1]];
	}
	return nullptr;
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, const TArray<int>& StartingLocation)
{
	if (!IsValid(Pawn))
	{
		return false;
	}

	UGridMovementComponent* GridMovementComp = Pawn->GetComponentByClass<UGridMovementComponent>();
	check(IsValid(GridMovementComp));

	AStageCell* StageCell = GetCell(StartingLocation);
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

	FVector CellLocation = FirstCell->GetActorLocation();

	float OriginCellX = CellLocation.X;

	for (int colIndex = 0; colIndex < Width; colIndex++)
	{
		CellLocation.X = OriginCellX;

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
				Cell = GetWorld()->SpawnActor<AStageCell>(StageCellClass, CellLocation, Rotation);
			}

			Cell->Initialize(colIndex, rowIndex);

			CellLocation.X += CellLength;

			Col.Add(Cell);
		}

		CellLocation.Y += CellWidth;

		Grid.Add(Col);
	}
}

void AStageGrid::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
}

