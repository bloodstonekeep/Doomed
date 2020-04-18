/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/InteractionInterface.h"
#include "InteractibleActor.generated.h"

UCLASS()
class DOOMED_API AInteractibleActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInteractibleActor();

	virtual void OnInteract_Implementation(AActor* interactor);
};
