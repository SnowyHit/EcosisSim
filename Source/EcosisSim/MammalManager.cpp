// Fill out your copyright notice in the Description page of Project Settings.


#include "MammalManager.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AMammalManager::AMammalManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMammalManager::BeginPlay()
{
	Super::BeginPlay();
}

void AMammalManager::SpawnMammal(EMammalType MammalType ,FVector3d Location)
{
	if(MammalType == EMammalType::Cat)
	{
		ACat* SpawnedCat = GetWorld()->SpawnActor<ACat>(CatRef);
		SpawnedCat->SetActorLocation(Location + FVector3d(0,0,30));
		SpawnedCat->SetActorScale3D(FVector3d(0.8f, 0.8f , 0.5f));
		Cats.Add(SpawnedCat);
		AllMammals.Add(SpawnedCat);
		SpawnedCat->OnDeath.AddDynamic(this , &AMammalManager::HandleMammalDeath);
		SpawnedCat->OnBreed.AddDynamic(this , &AMammalManager::BreedMammal);
	}
	else
	{
		AMouse* SpawnedMouse= GetWorld()->SpawnActor<AMouse>(MouseRef);
		SpawnedMouse->SetActorLocation(Location + FVector3d(0,0,30));
		SpawnedMouse->SetActorScale3D(FVector3d(0.8f, 0.8f , 0.5f));
		Mouses.Add(SpawnedMouse);
		AllMammals.Add(SpawnedMouse);
		SpawnedMouse->OnDeath.AddDynamic(this , &AMammalManager::HandleMammalDeath);
		SpawnedMouse->OnBreed.AddDynamic(this , &AMammalManager::BreedMammal);
	}
}

void AMammalManager::MoveMammals()
{
	for (auto Element : AllMammals)
	{
		Element->Move();
	}
}

void AMammalManager::BreedMammal(AMammal* MammalToBreed)
{
}

void AMammalManager::HandleMammalDeath(AMammal* DeadMammal)
{
	if(auto const Mouse = Cast<AMouse>(DeadMammal))
	{
		Mouses.Remove(Mouse);
	}
	if(auto const Cat = Cast<ACat>(DeadMammal))
	{
		Cats.Remove(Cat);
	}
	AllMammals.Remove(DeadMammal);
}

int AMammalManager::GetCatCount()
{
	return Cats.Num();
}

int AMammalManager::GetMouseCount()
{
	return Mouses.Num();
}

