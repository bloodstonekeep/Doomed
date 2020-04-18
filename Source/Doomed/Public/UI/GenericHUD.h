/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GenericHUD.generated.h"


UCLASS()
class DOOMED_API AGenericHUD : public AHUD
{
	GENERATED_BODY()

public:
    AGenericHUD();

	class TSubclassOf<UUserWidget> GetGameplayHUDClass() const { return gameplayHUDClass; }
	class TSubclassOf<UUserWidget> GetDeadMenuClass() const { return deadMenuClass; }
	class TSubclassOf<UUserWidget> GetPauseMenuClass() const { return pauseMenuClass; }

	bool ShowSpecificMenu(class TSubclassOf<class UUserWidget> classToShow, bool gameOnly, bool showMouse);

	UFUNCTION(BlueprintCallable, Category = "GenericHUD")
		void HideAllMenus();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> gameplayHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> deadMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GenericHUD")
		class TSubclassOf<UUserWidget> pauseMenuClass;
};
