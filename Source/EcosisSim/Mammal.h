// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "GameFramework/Actor.h"
#include "Mammal.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AMammal*, DeadMammal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBreedDelegate, AMammal*, BreedingMammal);
UCLASS()
class ECOSISSIM_API AMammal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMammal();

	FOnDeathDelegate OnDeath;
	FOnBreedDelegate OnBreed;
	UFUNCTION()
	virtual void Move();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlayTurn();
	virtual void Breed();
	virtual void Die();

	bool CanBreed;
	
	ABaseGrid* CurrentGrid;
	int Age;
};
