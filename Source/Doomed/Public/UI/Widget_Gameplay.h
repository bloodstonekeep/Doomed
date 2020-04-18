/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Gameplay.generated.h"


UCLASS()
class DOOMED_API UWidget_Gameplay : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintPure, Category = "Widget|Gameplay")
		float GetCurrentHealth();

	UFUNCTION(BlueprintPure, Category = "Widget|Gameplay")
		FText GetCurrentAmmo();
};
