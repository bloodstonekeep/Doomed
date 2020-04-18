// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PauseMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/PlayerCharacter.h"

bool UPauseMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
	}

	if (QuitToDesktopButton)
	{
		QuitToDesktopButton->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitToDesktopClicked);
	}

	if (QuitToMenuButton)
	{
		QuitToMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::OnQuitToMenuClicked);
	}

	return true;
}

void UPauseMenu::OnResumeClicked()
{
	if (auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		player->UnPauseGame();
	}
}

void UPauseMenu::OnQuitToMenuClicked()
{
	UGameplayStatics::OpenLevel(GetOwningPlayerPawn(), "Map_MainMenu");
}

void UPauseMenu::OnQuitToDesktopClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}
