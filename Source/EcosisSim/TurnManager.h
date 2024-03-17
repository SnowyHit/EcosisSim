// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "MammalManager.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

UCLASS()
class ECOSISSIM_API ATurnManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AMammalManager* MammalManager;
	AGridManager* GridManager;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
