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
	//We need to check if there's any mouse around us. 
	for (auto Element : CurrentGrid->Neighbors)
	{
		if(!Element.Value->IsGridFree())
		{
			if(auto const Mouse = Cast<AMouse>(Element.Value->CurrentActor)) // If there is
			{
				Mouse->Die(); // Eat it and move to that grid
				TimeTillLastEaten = 0;
				CurrentGrid->CurrentActor = nullptr;
				Element.Value->CurrentActor = this;
				CurrentGrid = Element.Value;
				return; //End the movement.
			}
		}
	}
	// if everything goes smooth
	Super::Move();
}

void ACat::Breed()
{
	Super::Breed();
	if(TimeTillLastEaten >= 3)
	{
		Die();
	}
}

