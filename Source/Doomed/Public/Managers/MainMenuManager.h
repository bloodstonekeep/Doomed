/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainMenuManager.generated.h"


UCLASS()
class DOOMED_API AMainMenuManager : public AGameModeBase
{
	GENERATED_BODY()

protected:

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Main menu")
        class TSubclassOf<UUserWidget> mainMenuClass;
};
