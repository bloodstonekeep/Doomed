#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class DOOMED_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintCallable, Category = "Character|Health")
		void SetCurrentHealth(float health) { CurrentHealth = health; }

	UFUNCTION(BlueprintPure, Category = "Character|Health")
		float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Character|Health")
		float GetMaxHealth() const { return MaxHealth; }
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Death")
		void OnDeath();
	
	virtual void OnDeath_Implementation() PURE_VIRTUAL(ACharacterBase::OnDeath_Implementation, );

protected:
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Health")
		float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		bool IsSprinting;
};
