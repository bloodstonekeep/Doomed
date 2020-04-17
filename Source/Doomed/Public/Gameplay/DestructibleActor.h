// Fill out your copyright notice in the Description page of Project Settings.

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
		void OnDestroy(class APlayerCharacter* collector);
	void OnDestroy_Implementation(class APlayerCharacter* collector);

protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
		class UParticleSystem* destroyParticle;
};
