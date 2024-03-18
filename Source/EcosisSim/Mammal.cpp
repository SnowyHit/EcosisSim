// Fill out your copyright notice in the Description page of Project Settings.


#include "Mammal.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AMammal::AMammal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMammal::BeginPlay()
{
	Super::BeginPlay();
}

void AMammal::PlayTurn()
{
	Age += 1;
	Move();
	Breed();
}

void AMammal::Breed()
{
	if(CanBreed)
	{
		OnBreed.Broadcast(this);
	}
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

void AMammal::Die()
{
	CurrentGrid->CurrentActor = nullptr;
	OnDeath.Broadcast(this);
	Destroy();
}

