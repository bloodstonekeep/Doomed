// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget_Gameplay.h"
#include "Characters/PlayerCharacter.h"
#include "Runtime/Core/Public/Internationalization/Text.h"

float UWidget_Gameplay::GetCurrentHealth()
{
	if (auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		const float maxHealth = player->GetMaxHealth();
		const float health = player->GetCurrentHealth();

		return FMath::Clamp<float>(health / maxHealth, 0.f, 1.f);
	}

	return 0.5f;
}

FText UWidget_Gameplay::GetCurrentAmmo()
{
	if (auto player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		return FText::AsNumber(player->GetCurrentAmmo());
	}

	return FText::FromString("???");
}