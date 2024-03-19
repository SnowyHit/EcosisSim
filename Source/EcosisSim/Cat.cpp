// Fill out your copyright notice in the Description page of Project Settings.


#include "Cat.h"

#include "Mouse.h"


// Sets default values
ACat::ACat()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACat::GainAge()
{
	Super::GainAge();
	TimeTillLastEaten +=1;
	if(Age >= 8)
	{
		CanBreed = true;
	}
}

void ACat::Move()
{
	for (auto Element : CurrentGrid->Neighbors)
	{
		if(!Element.Value->IsGridFree())
		{
			if(auto const Mouse = Cast<AMouse>(Element.Value->CurrentActor))
			{
				Mouse->Die();
				TimeTillLastEaten = 0;
				CurrentGrid->CurrentActor = nullptr;
				Element.Value->CurrentActor = this;
				CurrentGrid = Element.Value;
				this->SetActorLocation(Element.Value->GetActorLocation() + FVector3d(0,0,30));
				return;
			}
		}
	}
	if(auto const GridToMove  = CurrentGrid->GetRandomFreeNeighbor())
	{
		CurrentGrid->CurrentActor = nullptr;
		GridToMove->CurrentActor = this;
		CurrentGrid = GridToMove;
		this->SetActorLocation(GridToMove->GetActorLocation() + FVector3d(0,0,30));
	}
}

void ACat::Breed(AMammalManager* Spawner)
{
	Super::Breed(Spawner);
	if(TimeTillLastEaten >= 3)
	{
		Die();
	}
}

