#include "Characters/PlayerCharacter.h"

#include "Gameplay/HealthPickupActor.h"

void AHealthPickupActor::OnCollection_Implementation(class APlayerCharacter* collector)
{
	const float maxHealth = collector->GetMaxHealth();
	collector->SetCurrentHealth(maxHealth);

	APickupActor::OnCollection_Implementation(collector);
}