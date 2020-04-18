/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleActor.generated.h"

UCLASS()
class DOOMED_API ADestructibleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestructibleActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Destructible|Destroy")
		void OnDead();
	void OnDead_Implementation();

	virtual float TakeDamage(float damage, struct FDamageEvent const& damageEvent, class AController* eventInstigator, AActor* damageCauser) override;

protected:

	float currentHealth;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destructible|Health")
		float maxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destructible|Destroy")
		float destructionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destructible|Destroy")
		float destructionDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Destructible|Effects")
		class UParticleSystem* destroyParticle;
};
