// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "GameFramework/Actor.h"
#include "Mammal.generated.h"

UENUM(BlueprintType)
enum class EMammalType : uint8
{
	Cat UMETA(DisplayName = "Cat"),
	Mouse UMETA(DisplayName = "Mouse"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AMammal*, DeadMammal);
UCLASS()
class ECOSISSIM_API AMammal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMammal();

	FOnDeathDelegate OnDeath;
	UFUNCTION(BlueprintCallable)
	virtual void Move();
	
	UFUNCTION(BlueprintCallable)
	virtual void Breed(AMammalManager* Spawner);

	UFUNCTION(BlueprintCallable)
	virtual void GainAge();
	UPROPERTY(VisibleAnywhere)
	ABaseGrid* CurrentGrid;

	UPROPERTY(VisibleAnywhere)
	bool CanBreed;
	UPROPERTY(VisibleAnywhere)
	int Age;

	virtual void Die();
	EMammalType Type;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
