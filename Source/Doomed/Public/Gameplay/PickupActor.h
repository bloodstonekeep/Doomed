#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class DOOMED_API APickupActor : public AActor
{
	GENERATED_BODY()

public:
	APickupActor();

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PickupActor")
		void OnCollection(class APlayerCharacter* collector);
	virtual void OnCollection_Implementation(class APlayerCharacter* collector);

private:

	UFUNCTION()
		void OnSphereOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor,
			UPrimitiveComponent* otherComponent, int32 otherBodyIndex,
			bool fromSweep, const FHitResult& sweepResult);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USphereComponent* collectionSphere;
};