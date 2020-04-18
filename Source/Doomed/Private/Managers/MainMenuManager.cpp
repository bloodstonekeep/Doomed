/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#include "Managers/MainMenuManager.h"
#include "Blueprint/UserWidget.h"

void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();

	if (mainMenuClass)
	{
		if (auto player = GetWorld()->GetFirstPlayerController())
		{
			FInputModeUIOnly inputMode;

			inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			player->SetInputMode(inputMode);
			player->bShowMouseCursor = true;

			auto widget = CreateWidget<UUserWidget>(player, mainMenuClass);
			widget->AddToPlayerScreen();
		}
	}
}