#include "Gameplay/PickupActor.h"
#include "Components/SphereComponent.h"
#include "Characters/PlayerCharacter.h"

APickupActor::APickupActor()
{
	RootComponent = collectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	
	if (collectionSphere)
	{
		collectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
		collectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		collectionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnSphereOverlap);
	}
}

void APickupActor::OnCollection_Implementation(APlayerCharacter* collector)
{
	Destroy();
}

void APickupActor::OnSphereOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	auto player = Cast<APlayerCharacter>(otherActor);
	if (player)
	{
		OnCollection(player);
	}
}
