// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class ECOSISSIM_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridManager();
	
	//generate the grid
	UFUNCTION(BlueprintCallable)
	void GenerateGrid(int32 Size);

	UFUNCTION(BlueprintCallable)
	ABaseGrid* GetRandomFreeGrid();
	TArray<TArray<ABaseGrid*>> GetAllGrids() const { return GridCells;}
	
	UPROPERTY(EditAnywhere)
	UMaterialInterface* GridMat;

protected:
	virtual void BeginPlay() override;

private:
	 TArray<TArray<ABaseGrid*>> GridCells;
};
