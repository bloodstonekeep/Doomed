// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelEndActor.generated.h"

UCLASS()
class DOOMED_API ALevelEndActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelEndActor();

private:

	UFUNCTION()
		void OnBoxOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelEnd")
		FName NextLevelName;

private:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBillboardComponent* root_;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* collisionBox_;
};
