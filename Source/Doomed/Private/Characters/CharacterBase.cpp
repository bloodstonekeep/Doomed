#include "Characters/CharacterBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;

	IsSprinting = false;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentHealth != MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}