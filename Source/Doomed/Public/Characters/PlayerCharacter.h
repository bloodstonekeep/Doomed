// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
	*
	*/
UCLASS()
	class DOOMED_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UFUNCTION(BlueprintPure, Category = "Character|Gun|Ammo")
		int GetCurrentAmmo() const { return currentAmmo; }

	UFUNCTION(BlueprintPure, Category = "Character|Gun|Ammo")
		int GetMaxAmmo() const { return maxAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Character|Gun|Ammo")
		void SetCurrentAmmo(int newAmmo) { currentAmmo = newAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void MoveForward(float value);

	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void MoveRight(float value);

	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void LookUp(float value);

	UFUNCTION(BlueprintCallable, Category = "Character|Input|Movement")
		void Turn(float value);

	UFUNCTION(BlueprintCallable, Category = "Character|Input")
		void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Character|Input")
		void UnPauseGame();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* component) override;
	virtual void PossessedBy(AController* controller) override;
	virtual float TakeDamage(float damage,
		struct FDamageEvent const& damageEvent,
		class AController* eventInstigator,
		AActor* damageCauser) override;

	virtual void OnDeath_Implementation() override;

	bool HasAmmo() const { return (currentAmmo > 0); }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Movement")
		void OnSprintStart();
	void OnSprintStart_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Movement")
		void OnSprintEnd();
	void OnSprintEnd_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character|Input|Gun")
		void OnFire();
	void OnFire_Implementation();

private:

	void SpawnShootingParticles(FVector location);

protected:

	int currentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float cameraPitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float cameraPitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float baseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Camera")
		float baseLookUpRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Movement")
		float sprintSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UParticleSystem* hitEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UAnimMontage* fireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character|Gun")
		class UParticleSystem* trailEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun")
		float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun")
		bool canShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun|Ammo")
		bool unlimitedAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character|Gun|Ammo")
		int maxAmmo;

private:

	float previousSpeed_;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* camera_;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* springArm_;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* gunMesh_;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* skeletMesh_;

	UPROPERTY()
		class AGenericHUD* hud_;
};
