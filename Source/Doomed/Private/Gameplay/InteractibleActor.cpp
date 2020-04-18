// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/InteractibleActor.h"

// Sets default values
AInteractibleActor::AInteractibleActor()
{
}

void AInteractibleActor::OnInteract_Implementation(AActor* interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("Interating with: %s"), *interactor->GetName());
}
