/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"


UCLASS()
class DOOMED_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

private:

	UFUNCTION()
		void OnResumeClicked();

	UFUNCTION()
		void OnQuitToMenuClicked();

	UFUNCTION()
		void OnQuitToDesktopClicked();

public:

	UPROPERTY(meta = (BindWidget))
		class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitToMenuButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* QuitToDesktopButton;
};
