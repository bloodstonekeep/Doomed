// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/PickupActor.h"
#include "AmmoPickupActor.generated.h"

/**
 * 
 */
UCLASS()
class DOOMED_API AAmmoPickupActor : public APickupActor
{
	GENERATED_BODY()

protected:
	virtual void OnCollection_Implementation(class APlayerCharacter* collector) override;
};
