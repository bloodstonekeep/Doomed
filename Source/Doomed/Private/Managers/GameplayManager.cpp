/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#include "Managers/GameplayManager.h"

void AGameplayManager::RespawnPlayer(AController* controller)
{
	if (controller)
	{
		controller->GetPawn()->Destroy();

		RestartPlayer(controller);
	}
}