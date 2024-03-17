// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"

#include "GridManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATurnManager::ATurnManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	if(auto const MammalManagerRef = Cast<AMammalManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMammalManager::StaticClass())))
	{
		MammalManager = MammalManagerRef;
	}
	if(auto const GridManagerRef = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridManager::StaticClass())))
	{
		GridManager = GridManagerRef;
	}
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

