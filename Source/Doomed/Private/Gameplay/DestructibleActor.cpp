// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"

#include "EngineMinimal.h"
#include "Gameplay/DestructibleActor.h"
#include "Particles/ParticleSystemComponent.h"

ADestructibleActor::ADestructibleActor()
{
	RootComponent = mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (mesh)
	{
		mesh->SetCollisionObjectType(ECC_WorldDynamic);
	}

	destroyParticle = nullptr;
}

void ADestructibleActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructibleActor::OnDestroy_Implementation(APlayerCharacter* collector)
{
	auto location = GetActorLocation();
	auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), destroyParticle, location, FRotator::ZeroRotator, true);
}
