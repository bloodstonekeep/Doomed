// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UI/GenericHUD.h"

APlayerCharacter::APlayerCharacter()
	: previousSpeed_(0.f)
{
	springArm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (springArm_)
	{
		springArm_->SetupAttachment(GetCapsuleComponent());
		springArm_->RelativeLocation = FVector(-20.0f, 0.0f, 40.0f);
		springArm_->TargetArmLength = 0.0f;
		springArm_->bDoCollisionTest = false;
		springArm_->bUsePawnControlRotation = true;
		springArm_->bInheritPitch = false;
		springArm_->bInheritRoll = true;
		springArm_->bInheritYaw = true;
	}

	camera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("camera_"));
	if (camera_)
	{
		camera_->SetupAttachment(springArm_, USpringArmComponent::SocketName);
		camera_->FieldOfView = 90.0f;
	}

	skeletMesh_ = CreateDefaultSubobject <USkeletalMeshComponent>(TEXT("FP_Mesh"));
	if (skeletMesh_)
	{
		skeletMesh_->SetupAttachment(camera_);
	}

	gunMesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	if (gunMesh_)
	{
		gunMesh_->SetupAttachment(camera_);
	}

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	canShoot = true;
	unlimitedAmmo = false;
	maxAmmo = 10;
	currentAmmo = maxAmmo;

	baseTurnRate = 100.f;
	baseLookUpRate = 100.f;
	cameraPitchMax = 89.f;
	cameraPitchMin = -89.f;

	sprintSpeed = 1500.f;

	damage = 10.f;
	fireAnimation = nullptr;

	hitEffect = nullptr;
	trailEffect = nullptr;

	hud_ = nullptr;
}

void APlayerCharacter::MoveForward(float value)
{
	if (value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APlayerCharacter::LookUp(float value)
{
	auto deltaTime = GetWorld()->DeltaTimeSeconds;

	if (springArm_)
	{
		auto relativeRotation = springArm_->RelativeRotation;

		const float newPitch = FMath::ClampAngle(relativeRotation.Pitch + value * baseLookUpRate * deltaTime, cameraPitchMin, cameraPitchMax);

		relativeRotation.Pitch = newPitch;

		springArm_->SetRelativeRotation(relativeRotation);
	}
}

void APlayerCharacter::Turn(float value)
{
	auto deltaTime = GetWorld()->DeltaTimeSeconds;
	AddControllerYawInput(value * baseTurnRate * deltaTime);
}

void APlayerCharacter::PauseGame()
{
	if (auto player = Cast<APlayerController>(GetController()))
	{
		if (!hud_)
		{
			hud_ = Cast<AGenericHUD>(player->GetHUD());
		}

		hud_->ShowSpecificMenu(hud_->GetPauseMenuClass(), false, true);

		player->SetPause(true);
	}
}

void APlayerCharacter::UnPauseGame()
{
	if (auto player = Cast<APlayerController>(GetController()))
	{
		player->SetPause(false);

		if (!hud_)
		{
			hud_ = Cast<AGenericHUD>(player->GetHUD());
		}


		if (hud_)
		{
			hud_->ShowSpecificMenu(hud_->GetPauseMenuClass(), true, false);
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	gunMesh_->AttachToComponent(skeletMesh_, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("GripPoint"));

	if (currentAmmo != maxAmmo)
	{
		currentAmmo = maxAmmo;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

	check(inputComponent);

	inputComponent->BindAxis("MouseX", this, &APlayerCharacter::Turn);
	inputComponent->BindAxis("MouseY", this, &APlayerCharacter::LookUp);
	inputComponent->BindAxis("LeftRight", this, &APlayerCharacter::MoveRight);
	inputComponent->BindAxis("BackForward", this, &APlayerCharacter::MoveForward);

	inputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	inputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::OnFire);

	inputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::OnSprintEnd);
	inputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::OnSprintStart);
}

void APlayerCharacter::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	if (auto player = Cast<APlayerController>(controller))
	{
		hud_ = Cast<AGenericHUD>(player->GetHUD());
		if (hud_)
		{
			hud_->ShowSpecificMenu(hud_->GetGameplayHUDClass(), true, false);
		}
	}
}

float APlayerCharacter::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser)
{
	Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);

	if (CurrentHealth <= 0.f)
	{
		return 0.f;
	}

	const float healthChange = CurrentHealth - damageAmount;

	if (FMath::IsNearlyZero(healthChange) || healthChange <= 0.f)
	{
		CurrentHealth = 0.0f;
		OnDeath();
	}
	else
	{
		CurrentHealth = healthChange;
	}

	return CurrentHealth;
}

void APlayerCharacter::OnDeath_Implementation()
{
	canShoot = false;

	auto movement = GetCharacterMovement();

	movement->StopMovementImmediately();
	movement->DisableMovement();
	movement->SetJumpAllowed(false);

	gunMesh_->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);

	gunMesh_->SetHiddenInGame(true);
	skeletMesh_->SetHiddenInGame(true);

	if (!hud_)
	{
		if (auto player = Cast<APlayerController>(GetController()))
		{
			hud_ = Cast<AGenericHUD>(player->GetHUD());
		}
	}

	if (hud_)
	{
		hud_->ShowSpecificMenu(hud_->GetDeadMenuClass(), false, true);
	}
}

void APlayerCharacter::OnSprintStart_Implementation()
{
	canShoot = false;
	IsSprinting = true;

	auto movement = GetCharacterMovement();
	previousSpeed_ = movement->MaxWalkSpeed;
	movement->MaxWalkSpeed = sprintSpeed;
}

void APlayerCharacter::OnSprintEnd_Implementation()
{
	canShoot = true;
	IsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = previousSpeed_;
}

void APlayerCharacter::OnFire_Implementation()
{
	if (!canShoot 
		|| (!HasAmmo() && !unlimitedAmmo))
	{
		return;
	}

	auto location = FVector::ZeroVector;
	FHitResult hit;
	const FVector rayStart = camera_->GetComponentLocation();
	const FVector rayEnd = rayStart + (camera_->GetForwardVector() * 10000.0f);

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(GetOwner());
	queryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, rayStart, rayEnd, ECollisionChannel::ECC_Visibility, queryParams);

	if (hit.bBlockingHit && hit.GetActor())
	{
		location = hit.ImpactPoint;

		TSubclassOf<UDamageType> const validDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());

		FPointDamageEvent pointDamageEvent(damage, hit, hit.ImpactNormal, validDamageTypeClass);

		hit.GetActor()->TakeDamage(damage, pointDamageEvent, GetController(), GetOwner());
	}
	else
	{
		location = rayEnd;
	}

	SpawnShootingParticles(location);

	if (fireAnimation)
	{
		if (auto animInstance = skeletMesh_->GetAnimInstance())
		{
			animInstance->Montage_Play(fireAnimation);
		}
	}

	if (!unlimitedAmmo)
	{
		currentAmmo--;
	}
}

void APlayerCharacter::SpawnShootingParticles(FVector location)
{
	if (trailEffect)
	{
		auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), trailEffect, gunMesh_->GetSocketLocation(FName("Muzzle")));
		particle->SetWorldScale3D(FVector(5.f));
		particle->SetVectorParameter(FName("ShockBeamEnd"), location);
	}

	if (hitEffect)
	{
		auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, location, FRotator::ZeroRotator, true);
		particle->SetWorldScale3D(FVector(.25f));
	}
}
