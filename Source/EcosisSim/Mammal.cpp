#include "Mammal.h"

#include "MammalManager.h"

AMammal::AMammal()
{
	
	PrimaryActorTick.bCanEverTick = true;
}

void AMammal::BeginPlay()
{
	Super::BeginPlay();
}


void AMammal::Breed(AMammalManager* Spawner)
{
	if(CanBreed)
	{
		if(auto const NeighborToBreed = CurrentGrid->GetRandomFreeNeighbor())
		{
			Spawner->SpawnMammal(Type ,NeighborToBreed->GetActorLocation() , NeighborToBreed);
		}
		CanBreed = false;
	}
}

void AMammal::GainAge()
{
	Age += 1;
}

void AMammal::Move()
{
	if(auto const GridToMove  = CurrentGrid->GetRandomFreeNeighbor())
	{
		CurrentGrid->CurrentActor = nullptr;
		GridToMove->CurrentActor = this;
		CurrentGrid = GridToMove;
		this->SetActorLocation(GridToMove->GetActorLocation() + FVector3d(0,0,30));
	}
}

void AMammal::Die()
{
	CurrentGrid->CurrentActor = nullptr;
	OnDeath.Broadcast(this);
	Destroy();
}

