// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

#include "MammalManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGridManager::AGridManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGridManager::GenerateGrid(int32 Size)
{
	// Resize the grid array to match the specified size
	GridCells.SetNum(Size);
	for (int32 i = 0; i < Size; ++i)
	{
		GridCells[i].SetNum(Size);
	}

	// Spawn grid cells
	for (int32 Row = 0; Row < Size; ++Row)
	{
		for (int32 Col = 0; Col < Size; ++Col)
		{
			ABaseGrid* NewCell = GetWorld()->SpawnActor<ABaseGrid>(ABaseGrid::StaticClass());
			GridCells[Row][Col] = NewCell;
			NewCell->SetCoordinates(Row, Col); // Set coordinates for the cell
			NewCell->SetMaterial(GridMat); // Set the MaterialForGrid
		}
	}

	// Set neighbors for each grid cell
	for (int32 Row = 0; Row < Size; ++Row)
	{
		for (int32 Col = 0; Col < Size; ++Col)
		{
			ABaseGrid* CurrentCell = GridCells[Row][Col];

			// Top neighbor
			if (Row > 0)
				CurrentCell->SetNeighbors(GridCells[Row - 1][Col], nullptr, nullptr, nullptr);

			// Bottom neighbor
			if (Row < Size - 1)
				CurrentCell->SetNeighbors(nullptr, GridCells[Row + 1][Col], nullptr, nullptr);

			// Left neighbor
			if (Col > 0)
				CurrentCell->SetNeighbors(nullptr, nullptr, nullptr, GridCells[Row][Col - 1]);

			// Right neighbor
			if (Col < Size - 1)
				CurrentCell->SetNeighbors(nullptr, nullptr, GridCells[Row][Col + 1], nullptr);
		}
	}
}

ABaseGrid* AGridManager::GetRandomFreeGrid()
{
	TArray<ABaseGrid*> FreeGrids;
	for (auto Element : GetAllGrids())
	{
		for (auto BaseGrid : Element)
		{
			if(!IsValid(BaseGrid->CurrentActor))
			{
				FreeGrids.Add(BaseGrid);
			}
		}
	}

	if (FreeGrids.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, FreeGrids.Num() - 1);

		return FreeGrids[RandomIndex];
	}

	return nullptr;
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

