#include "Gameplay/HealthPickupActor.h"

#include "Characters/PlayerCharacter.h"

void AHealthPickupActor::OnCollection_Implementation(class APlayerCharacter* collector)
{
	const float currentHealth = collector->GetCurrentHealth();
	const float maxHealth = collector->GetMaxHealth();

	if (currentHealth == maxHealth)
	{
		return;
	}

	collector->SetCurrentHealth(maxHealth);

	APickupActor::OnCollection_Implementation(collector);
}