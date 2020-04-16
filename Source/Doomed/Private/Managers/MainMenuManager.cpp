// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"

#include "Managers/MainMenuManager.h"

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