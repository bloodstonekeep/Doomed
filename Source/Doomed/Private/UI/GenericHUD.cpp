// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GenericHUD.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

AGenericHUD::AGenericHUD()
{
	deadMenuClass = NULL;
	pauseMenuClass = NULL;
	gameplayHUDClass = NULL;
}

bool AGenericHUD::ShowSpecificMenu(TSubclassOf<class UUserWidget> classToShow, bool gameOnly, bool showMouse)
{
	HideAllMenus();

	if (classToShow)
	{
		auto CreatedWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), classToShow);
		CreatedWidget->AddToPlayerScreen();

		if (gameOnly)
		{
			GetOwningPlayerController()->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			FInputModeUIOnly inputMode;

			inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			GetOwningPlayerController()->SetInputMode(inputMode);
		}

		GetOwningPlayerController()->bShowMouseCursor = showMouse;

		return true;
	}

	return false;
}

void AGenericHUD::HideAllMenus()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
