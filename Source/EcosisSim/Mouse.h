// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mammal.h"
#include "Mouse.generated.h"

UCLASS()
class ECOSISSIM_API AMouse : public AMammal
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMouse();
	virtual void GainAge() override;
};
