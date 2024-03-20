// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGrid.h"


// Sets default values
ABaseGrid::ABaseGrid()
{
	Neighbors = TMap<EDirection , ABaseGrid*>();
	GridX = 0;
	GridY = 0;
	// Create and attach the visual mesh component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = VisualMesh;

	// Set default box mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMesh.Succeeded())
	{
		VisualMesh->SetStaticMesh(DefaultMesh.Object);
	}
}

// Called when the game starts or when spawned
void ABaseGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseGrid::SetCoordinates(int32 X, int32 Y)
{
	GridX = X;
	GridY = Y;

	// Set position based on coordinates
	FVector CellPosition = FVector(GridX * 100.0f, GridY * 100.0f, 0.0f); // Assuming each cell is 100 units wide
	SetActorLocation(CellPosition);
	SetActorScale3D(FVector3d(1 , 1, 0.2f));
}
//For every grid , i want to know its neighbours so this function is a must call.
void ABaseGrid::SetNeighbors(ABaseGrid* North, ABaseGrid* South, ABaseGrid* East, ABaseGrid* West)
{
	if (North != nullptr)
	{
		Neighbors.Add(EDirection::North,North);
	}
	if (South != nullptr)
	{
		Neighbors.Add(EDirection::South,South);
	}
	if (East != nullptr)
	{
		Neighbors.Add(EDirection::East,East);
	}
	if (West != nullptr)
	{
		Neighbors.Add(EDirection::West,West);
	}
}

ABaseGrid* ABaseGrid::GetRandomFreeNeighbor()
{
	if (Neighbors.IsEmpty())
	{
		return nullptr; // No neighbors
	}

	//Array for free grids
	TArray<ABaseGrid*> FreeGrids;
	for (auto Pair : Neighbors)
	{
		if(Pair.Value->IsGridFree())
		{
			FreeGrids.Add(Pair.Value);
		}
	}
	
	if(FreeGrids.IsEmpty())
	{
		return nullptr;
	}
	
	int32 RandomIndex = FMath::RandRange(0, FreeGrids.Num() - 1);
	return FreeGrids[RandomIndex];
}

bool ABaseGrid::IsGridFree()
{
	return !IsValid(CurrentActor);
}


void ABaseGrid::SetMaterial(UMaterialInterface* Material)
{
	if (VisualMesh)
	{
		VisualMesh->SetMaterial(0, Material);
	}
}


