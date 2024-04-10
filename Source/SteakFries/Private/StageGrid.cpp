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

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int X)
{
	TArray<int> ToGridLocation = FromCell->GetGridLocation();

	ToGridLocation[1] = std::clamp(ToGridLocation[1] + X, 0, Width - 1);
	
	// TODO: add blocking

	AStageCell* ToCell = GetCell(ToGridLocation);

	AActor* Actor = FromCell->Empty();
	ToCell->Fill(Actor);

	return ToCell;
}

AStageCell* AStageGrid::TryMoveY(AStageCell* FromCell, int Y)
{
	TArray<int> ToGridLocation = FromCell->GetGridLocation();

	ToGridLocation[0] = std::clamp(ToGridLocation[0] - Y, 0, Height - 1);

	AStageCell* ToCell = GetCell(ToGridLocation);

	AActor* Actor = FromCell->Empty();
	ToCell->Fill(Actor);

	return ToCell;
}

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

