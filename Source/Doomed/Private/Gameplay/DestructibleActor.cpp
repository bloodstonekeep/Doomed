// Fill out your copyright notice in the Description page of Project Settings.

#include "Gameplay/DestructibleActor.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

ADestructibleActor::ADestructibleActor()
{
	RootComponent = mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (mesh)
	{
		mesh->SetCollisionObjectType(ECC_WorldDynamic);
	}

	maxHealth = 25.f;
	currentHealth = maxHealth;
	destructionRadius = 400.f;
	destructionDamage = 25.f;

	destroyParticle = nullptr;
}

void ADestructibleActor::BeginPlay()
{
	Super::BeginPlay();

	if (currentHealth != maxHealth)
	{
		currentHealth = maxHealth;
	}
}

void ADestructibleActor::OnDead_Implementation()
{
	auto location = GetActorLocation();
	auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroyParticle, location, FRotator::ZeroRotator, true);

	TArray<FOverlapResult> overlaps;

	const FVector startPos = mesh->GetComponentLocation();

	auto sphere = FCollisionShape::MakeSphere(destructionRadius);

	if (GetWorld()->OverlapMultiByChannel(overlaps, startPos,
		FQuat::Identity, ECC_WorldDynamic, sphere))
	{
		for (int index = 0; index < overlaps.Num(); index++)
		{
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());

			FDamageEvent DamageEvent(ValidDamageTypeClass);
			
			auto actor = overlaps[index].Actor;
			if (actor.IsValid() && actor != this)
			{
				actor->TakeDamage(destructionDamage, DamageEvent, nullptr, this);
			}
		}
	}

	Destroy();
}

float ADestructibleActor::TakeDamage(float damage, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	Super::TakeDamage(damage, damageEvent, eventInstigator, damageCauser);

	if (currentHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float newHealth = currentHealth - damage;

	if (FMath::IsNearlyZero(newHealth) || newHealth < 0.0f)
	{
		currentHealth = 0.0f;
		OnDead();

		return 0;
	}

	currentHealth = newHealth;

	return currentHealth;
}
