// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGrid.h"
#include "StageCell.h"
#include "CharacterSpawner.h"
#include "GridMovement.h"

AStageGrid::AStageGrid()
{

}

void AStageGrid::Initialize(ACharacterSpawner* CharacterSpawner)
{
	if (IsValid(CharacterSpawner))
	{
		CharacterSpawner->OnCharacterPawnSpawned.AddUniqueDynamic(this, &AStageGrid::OnPlayerPawnSpawned);
	}
}

PRAGMA_DISABLE_OPTIMIZATION;

bool AStageGrid::TryMoveX(AStageCell* FromCell, int X, AStageCell** OutToStageCell)
{
	if (X == 0)
	{
		return false;
	}

	TArray<int> CurCellLocation = FromCell->GetGridLocation();

	if ((X > 0 && CurCellLocation[1] == Width - 1) ||
		(X < 0 && CurCellLocation[1] == 0))
	{
		return false;
	}

	int Direction = X > 0 ? 1 : -1;
	TArray<int> NextCellLocation = CurCellLocation;
	NextCellLocation[1] += Direction;
	AStageCell* NextCell = GetCell(NextCellLocation);

	if (NextCell->IsFilled())
	{
		return false;
	}

	while (X != 0 && NextCellLocation[1] < Width && NextCellLocation[1] >= 0 && !NextCell->IsFilled())
	{
		X -= Direction;
		CurCellLocation = NextCellLocation;
		NextCellLocation[1] += Direction;
		NextCell = GetCell(NextCellLocation);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurCellLocation);
	CurCell->Fill(Actor);
	*OutToStageCell = CurCell;

	return true;
}

bool AStageGrid::TryMoveY(AStageCell* FromCell, int Y, AStageCell** OutToStageCell)
{
	if (Y == 0)
	{
		return false;
	}

	TArray<int> CurCellLocation = FromCell->GetGridLocation();

	if ((Y > 0 && CurCellLocation[0] == 0) ||
		(Y < 0 && CurCellLocation[0] == Height - 1))
	{
		return false;
	}

	int Direction = Y > 0 ? -1 : 1;
	TArray<int> NextCellLocation = CurCellLocation;
	NextCellLocation[0] += Direction;
	AStageCell* NextCell = GetCell(NextCellLocation);

	if (NextCell->IsFilled())
	{
		return false;
	}

	while (Y != 0 && NextCellLocation[0] < Height && NextCellLocation[0] >= 0 && !NextCell->IsFilled())
	{
		Y += Direction;
		CurCellLocation = NextCellLocation;
		NextCellLocation[0] += Direction;
		NextCell = GetCell(NextCellLocation);
	}

	AActor* Actor = FromCell->Empty();
	AStageCell* CurCell = GetCell(CurCellLocation);
	CurCell->Fill(Actor);
	*OutToStageCell = CurCell;

	return true;
}

PRAGMA_ENABLE_OPTIMIZATION;

AStageCell* AStageGrid::GetCell(const TArray<int>& Location)
{
	if (Location[0] >= 0 && Location[0] < Height && Location[1] >= 0 && Location[1] < Width)
	{
		return Grid[Location[0]][Location[1]];
	}
	return nullptr;
}

void AStageGrid::OnPlayerPawnSpawned(APawn* PlayerPawn, const TArray<int>& StartingLocation)
{
	InitializeOnGrid(PlayerPawn, StartingLocation);
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, const TArray<int>& StartingLocation)
{
	if (!IsValid(Pawn))
	{
		return false;
	}

	UGridMovement* GridMovementComp = Pawn->GetComponentByClass<UGridMovement>();

	if (!IsValid(GridMovementComp))
	{
		return false;
	}

	AStageCell* StageCell = GetCell(StartingLocation);

	if (!IsValid(StageCell))
	{
		return false;
	}

	Pawn->SetActorLocation(StageCell->GetActorLocation());
	StageCell->Fill(Pawn);
	
	GridMovementComp->Initialize(this, StageCell);

	return true;
}

void AStageGrid::CreateGrid()
{
	FRotator Rotation = GetActorRotation();

	AStageCell* FirstCell = GetWorld()->SpawnActor<AStageCell>(StageCellClass, GetActorLocation(), Rotation);

	float CellLength = FirstCell->GetLength();
	float CellWidth = FirstCell->GetWidth();

	FirstCell->SetActorRelativeLocation(FVector(-CellLength / 2.0f, 0.0f, 0.0f));

	FVector CellLocation = FirstCell->GetActorLocation();

	float OriginCellY = CellLocation.Y + CellWidth / 2.0f;

	for (int rowIndex = 0; rowIndex < Height; rowIndex++)
	{
		CellLocation.Y = OriginCellY;

		TArray<AStageCell*> Row;

		for (int colIndex = 0; colIndex < Width; colIndex++)
		{
			AStageCell* Cell;
			if (rowIndex == 0 && colIndex == 0)
			{
				Cell = FirstCell;
				Cell->SetActorLocation(CellLocation);
			}
			else
			{
				Cell = GetWorld()->SpawnActor<AStageCell>(StageCellClass, CellLocation, Rotation);
			}

			Cell->Initialize(rowIndex, colIndex);

			CellLocation.Y += CellWidth;

			Row.Add(Cell);
		}

		CellLocation.X -= CellLength;

		Grid.Add(Row);
	}
}

void AStageGrid::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
}

