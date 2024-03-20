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

void AMammalManager::SpawnMammal(EMammalType MammalType ,FVector3d Location , ABaseGrid* GridToSpawn , bool isBreeding)
{
	if(MammalType == EMammalType::Cat)
	{
		ACat* SpawnedCat = GetWorld()->SpawnActor<ACat>(CatRef);
		SpawnedCat->SetActorLocation(Location + FVector3d(0,0,30));
		SpawnedCat->SetActorScale3D(FVector3d(0.8f, 0.8f , 0.5f));
		SpawnedCat->CurrentGrid = GridToSpawn;
		GridToSpawn->CurrentActor = SpawnedCat;
		SpawnedCat->Type = MammalType;
		SpawnedCat->SpawnerClass = this;
		if(isBreeding)
		{
			NewlyBredCats.Add(SpawnedCat);
		}
		else
		{
			Cats.Add(SpawnedCat);
			AllMammals.Add(SpawnedCat);
		}
		SpawnedCat->OnDeath.AddDynamic(this , &AMammalManager::HandleMammalDeath);
	}
	else
	{
		AMouse* SpawnedMouse= GetWorld()->SpawnActor<AMouse>(MouseRef);
		SpawnedMouse->SetActorLocation(Location + FVector3d(0,0,30));
		SpawnedMouse->SetActorScale3D(FVector3d(0.8f, 0.8f , 0.5f));
		SpawnedMouse->CurrentGrid = GridToSpawn;
		GridToSpawn->CurrentActor = SpawnedMouse;
		SpawnedMouse->Type = MammalType;
		SpawnedMouse->SpawnerClass = this;
		if(isBreeding)
		{
			NewlyBredMouses.Add(SpawnedMouse);
		}
		else
		{
			Mouses.Add(SpawnedMouse);
			AllMammals.Add(SpawnedMouse);
		}
		SpawnedMouse->OnDeath.AddDynamic(this , &AMammalManager::HandleMammalDeath);
	}
}

void AMammalManager::StartMammalsTurn()
{
	MammalPlayingTurn = 0;
	if(!AllMammals.IsEmpty())
	{
		AllMammals[0]->Move();
		AllMammals[0]->StartPhysicalMovement();
		AllMammals[0]->OnMovementEnded.AddDynamic(this , &AMammalManager::MammalMovementChain);
	}
}

void AMammalManager::BreedMammals()
{
	TArray<AMammal*> CurrentMammals = AllMammals;
	for (auto Element : CurrentMammals)
	{
		Element->Breed();
	}
}

void AMammalManager::AgeMammals()
{
	for (auto Element : AllMammals)
	{
		Element->GainAge();
	}
}

void AMammalManager::MammalMovementChain(AMammal* MovingMammal)
{
	MammalPlayingTurn+=1;
	if(AllMammals.Num() > MammalPlayingTurn)
	{
		AllMammals[MammalPlayingTurn]->Move();
		AllMammals[MammalPlayingTurn]->StartPhysicalMovement();
		AllMammals[MammalPlayingTurn]->OnMovementEnded.AddDynamic(this , &AMammalManager::MammalMovementChain);
	}
	else
	{
		OnAllMovementEnded.Broadcast();
		AgeMammals();
		BreedMammals();
		HandleNewlyBredLists();
	}
	MovingMammal->OnMovementEnded.Clear();
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

void AMammalManager::HandleNewlyBredLists()
{
	Cats.Append(NewlyBredCats);
	Mouses.Append(NewlyBredMouses);
	AllMammals.Append(NewlyBredCats);
	AllMammals.Append(NewlyBredMouses);
	NewlyBredMouses.Empty();
	NewlyBredCats.Empty();
}

int AMammalManager::GetCatCount()
{
	return Cats.Num();
}

int AMammalManager::GetMouseCount()
{
	return Mouses.Num();
}

