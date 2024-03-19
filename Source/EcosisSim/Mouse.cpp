// Fill out your copyright notice in the Description page of Project Settings.


#include "Mouse.h"


// Sets default values
AMouse::AMouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMouse::GainAge()
{
	Super::GainAge();
	if(Age >= 3)
	{
		CanBreed = true;
	}
}


