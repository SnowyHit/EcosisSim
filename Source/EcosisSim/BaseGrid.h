// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrid.generated.h"

UENUM(BlueprintType)
enum class EDirection : uint8
{
	North UMETA(DisplayName = "North"),
	South UMETA(DisplayName = "South"),
	East UMETA(DisplayName = "East"),
	West UMETA(DisplayName = "West")
};

UCLASS()
class ECOSISSIM_API ABaseGrid : public AActor
{
	GENERATED_BODY()

public:
	ABaseGrid();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	int32 GridX;
	int32 GridY;

	void SetCoordinates(int32 X, int32 Y);
	void SetNeighbors(ABaseGrid* North, ABaseGrid* South, ABaseGrid* East, ABaseGrid* West);
	void SetMaterial(UMaterialInterface* Material); 

	UFUNCTION()
	ABaseGrid* GetRandomFreeNeighbor();
	
	UPROPERTY(VisibleAnywhere)
	AActor* CurrentActor;
	
	UFUNCTION()
	bool IsGridFree();
	
	UPROPERTY(VisibleAnywhere)
	TMap<EDirection, ABaseGrid*> Neighbors;
protected:
	virtual void BeginPlay() override;
private:
};
