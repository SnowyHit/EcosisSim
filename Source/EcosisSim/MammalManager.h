﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cat.h"
#include "Mouse.h"
#include "GameFramework/Actor.h"
#include "MammalManager.generated.h"
UENUM(BlueprintType)
enum class EMammalType : uint8
{
	Cat UMETA(DisplayName = "Cat"),
	Mouse UMETA(DisplayName = "Mouse"),
};
UCLASS()
class ECOSISSIM_API AMammalManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMammalManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ACat> CatRef;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMouse> MouseRef;
	UFUNCTION(BlueprintCallable)
	int GetCatCount();
	UFUNCTION(BlueprintCallable)
	int GetMouseCount();
	TArray<AMammal*> AllMammals;
	TArray<ACat*> Cats;
	TArray<AMouse*> Mouses;
	UFUNCTION()
	void HandleMammalDeath(AMammal* DeadMammal);
	
public:
	UFUNCTION()
	void SpawnMammal(EMammalType MammalType ,FVector3d Location);
	UFUNCTION()
	void MoveMammals();
	UFUNCTION()
	void BreedMammal(AMammal* MammalToBreed);
	
	TArray<AMammal*> GetAllMammals() const { return AllMammals;}
	TArray<ACat*> GetAllCats() const { return Cats;}
	TArray<AMouse*> GetAllMouses() const { return Mouses;}
	
};
