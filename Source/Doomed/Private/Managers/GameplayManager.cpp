// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/GameplayManager.h"

void AGameplayManager::RespawnPlayer(AController* controller)
{
	if (controller)
	{
		controller->GetPawn()->Destroy();

		RestartPlayer(controller);
	}
}