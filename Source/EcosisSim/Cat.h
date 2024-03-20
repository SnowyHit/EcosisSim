// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mammal.h"
#include "Cat.generated.h"

UCLASS()
class ECOSISSIM_API ACat : public AMammal
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACat();

	virtual void GainAge() override;
	virtual void Move() override;
	virtual void Breed() override;
	
	int TimeTillLastEaten;
};
