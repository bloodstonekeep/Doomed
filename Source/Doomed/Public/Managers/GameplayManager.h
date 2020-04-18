/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayManager.generated.h"


UCLASS()
class DOOMED_API AGameplayManager : public AGameModeBase
{
	GENERATED_BODY()

public:
    
    UFUNCTION(BlueprintCallable, Category = "Game")
        void RespawnPlayer(AController* controller);
};
