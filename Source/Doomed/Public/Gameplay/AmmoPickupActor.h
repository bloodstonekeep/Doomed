/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Gameplay/PickupActor.h"
#include "AmmoPickupActor.generated.h"

UCLASS()
class DOOMED_API AAmmoPickupActor : public APickupActor
{
	GENERATED_BODY()

protected:
	virtual void OnCollection_Implementation(class APlayerCharacter* collector) override;
};
