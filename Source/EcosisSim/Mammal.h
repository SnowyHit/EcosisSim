// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "GameFramework/Actor.h"
#include "Mammal.generated.h"

UCLASS()
class ECOSISSIM_API AMammal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMammal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlayTurn();
	virtual void Breed();
	virtual void Move();
	virtual void Die();

	bool CanBreed;
	
	ABaseGrid* CurrentGrid;
	
	int Age;
};
