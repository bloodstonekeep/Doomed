/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/


#include "Gameplay/InteractibleActor.h"

// Sets default values
AInteractibleActor::AInteractibleActor()
{
}

void AInteractibleActor::OnInteract_Implementation(AActor* interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interating with: %s"), *interactor->GetName());
}
