// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGrid.h"
#include "StageCell.h"
#include "CharacterSpawner.h"
#include "GridMovement.h"

PRAGMA_DISABLE_OPTIMIZATION;

AStageGrid::AStageGrid()
{

}

void AStageGrid::Initialize(ACharacterSpawner* CharacterSpawner)
{
	if (IsValid(CharacterSpawner))
	{
		CharacterSpawner->OnPlayerPawnSpawned.AddUniqueDynamic(this, &AStageGrid::OnPlayerPawnSpawned);
	}
}

AStageCell* AStageGrid::TryMoveX(AStageCell* FromCell, int X)
{
	int TargetRow = FromCell->GetRow();
	int TargetCol = FromCell->GetCol() + X;

	TargetCol = std::clamp(TargetCol, 0, Width - 1);
	
	// TODO: add blocking

	AStageCell* ToCell = Grid[TargetRow][TargetCol];

	AActor* Actor = FromCell->Empty();
	ToCell->Fill(Actor);

	return ToCell;
}

AStageCell* AStageGrid::TryMoveY(AStageCell* FromCell, int Y)
{
	int TargetRow = FromCell->GetRow() - Y;
	int TargetCol = FromCell->GetCol();

	TargetRow = std::clamp(TargetRow, 0, Height - 1);

	AStageCell* ToCell = Grid[TargetRow][TargetCol];

	AActor* Actor = FromCell->Empty();
	ToCell->Fill(Actor);

	return ToCell;
}

void AStageGrid::OnPlayerPawnSpawned(APawn* PlayerPawn)
{
	InitializeOnGrid(PlayerPawn, 0, 0);
}

bool AStageGrid::InitializeOnGrid(APawn* Pawn, int Row, int Col)
{
	if (!IsValid(Pawn) || Row >= Height || Col >= Width)
	{
		return false;
	}

	UGridMovement* GridMovementComp = Pawn->GetComponentByClass<UGridMovement>();

	if (!IsValid(GridMovementComp))
	{
		return false;
	}

	AStageCell* StageCell = Grid[Row][Col];
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

PRAGMA_ENABLE_OPTIMIZATION;

