#include "Characters/PlayerCharacter.h"

#include "Gameplay/AmmoPickupActor.h"

void AAmmoPickupActor::OnCollection_Implementation(class APlayerCharacter* collector)
{
	const float maxAmmo = collector->GetMaxAmmo();
	collector->SetCurrentAmmo(maxAmmo);

	APickupActor::OnCollection_Implementation(collector);
}