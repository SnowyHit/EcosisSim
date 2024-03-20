#include "Mammal.h"

#include "MammalManager.h"

AMammal::AMammal()
{
	
	PrimaryActorTick.bCanEverTick = true;
}
void AMammal::Breed()
{
	if(CanBreed)
	{
		if(auto const NeighborToBreed = CurrentGrid->GetRandomFreeNeighbor())
		{
			SpawnerClass->SpawnMammal(Type ,NeighborToBreed->GetActorLocation() , NeighborToBreed ,true);
		}
		CanBreed = false;
	}
}

void AMammal::GainAge()
{
	Age += 1;
}

void AMammal::MovementEnded()
{
	OnMovementEnded.Broadcast(this);
}

void AMammal::Move()
{
	if(auto const GridToMove  = CurrentGrid->GetRandomFreeNeighbor())
	{
		CurrentGrid->CurrentActor = nullptr;
		GridToMove->CurrentActor = this;
		CurrentGrid = GridToMove;
	}
}

void AMammal::StartPhysicalMovement_Implementation()
{
	
}

void AMammal::Die()
{
	CurrentGrid->CurrentActor = nullptr;
	OnDeath.Broadcast(this);
	Destroy();
}

