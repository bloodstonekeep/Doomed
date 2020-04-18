#pragma once

#include "CoreMinimal.h"
#include "Gameplay/PickupActor.h"
#include "HealthPickupActor.generated.h"


UCLASS()
class DOOMED_API AHealthPickupActor : public APickupActor
{
	GENERATED_BODY()

protected:
	virtual void OnCollection_Implementation(class APlayerCharacter* collector) override;

};
