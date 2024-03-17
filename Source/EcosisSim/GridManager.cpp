// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"


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

	// Create grid cells and set their neighbors
	for (int32 Row = 0; Row < Size; ++Row)
	{
		for (int32 Col = 0; Col < Size; ++Col)
		{
			ABaseGrid* NewCell = GetWorld()->SpawnActor<ABaseGrid>(ABaseGrid::StaticClass());
			GridCells[Row][Col] = NewCell;
			NewCell->SetCoordinates(Row, Col); // Set coordinates for the cell
			NewCell->SetMaterial(GridMat); //Set The MaterialForGrid
			// Set neighbors for the cell
			if (Row > 0) // Check if not in the top row
				{
				NewCell->SetNeighbors(GridCells[Row - 1][Col], nullptr, nullptr, nullptr);
				}
			if (Row < Size - 1) // Check if not in the bottom row
				{
				NewCell->SetNeighbors(nullptr, GridCells[Row + 1][Col], nullptr, nullptr);
				}
			if (Col > 0) // Check if not in the leftmost column
				{
				NewCell->SetNeighbors(nullptr, nullptr, nullptr, GridCells[Row][Col - 1]);
				}
			if (Col < Size - 1) // Check if not in the rightmost column
				{
				NewCell->SetNeighbors(nullptr, nullptr, GridCells[Row][Col + 1], nullptr);
				}
		}
	}
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

