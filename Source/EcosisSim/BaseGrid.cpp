// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGrid.h"


// Sets default values
ABaseGrid::ABaseGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
	SetActorScale3D(FVector3d(0.95f , 0.95f, 0.2f));
}

void ABaseGrid::SetNeighbors(ABaseGrid* North, ABaseGrid* South, ABaseGrid* East, ABaseGrid* West)
{
	Neighbors.Empty(); // Clear existing neighbors

	// Add provided neighbors to the array
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

ABaseGrid* ABaseGrid::GetRandomFreeNeighbor() const
{
	if (Neighbors.Num() == 0)
	{
		return nullptr; // No neighbors
	}
	
	TArray<EDirection> DirectionArray;
	Neighbors.GenerateKeyArray(DirectionArray);
	for (auto Direction : DirectionArray)
	{
		if(auto const grid =  Neighbors[Direction])
		{
			if(!IsValid(grid->CurrentActor))
			{
				DirectionArray.Remove(Direction);
			}
		}
	}
	int32 RandomIndex = FMath::RandRange(0, DirectionArray.Num() - 1);
	if(RandomIndex <= 0)
	{
		return nullptr;
	}
	return Neighbors[DirectionArray[RandomIndex]];
}


void ABaseGrid::SetMaterial(UMaterialInterface* Material)
{
	if (VisualMesh)
	{
		VisualMesh->SetMaterial(0, Material); // Assuming you have only one material slot
	}
}


