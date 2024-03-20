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
	ATurnManager();

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void StartGame(int32 GridSize , int32 CatCount , int32 MouseCount);
	UFUNCTION(BlueprintCallable)
	void ContinueRound();
	UPROPERTY()
	AMammalManager* MammalManager;
	UPROPERTY()
	AGridManager* GridManager;
public:

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	int RoundCount;
};
