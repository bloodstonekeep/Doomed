/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

#include "Gameplay/LevelEndActor.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Characters/PlayerCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelEndActor::ALevelEndActor()
{
	RootComponent = root_ = CreateDefaultSubobject<UBillboardComponent>(TEXT("Root"));

	collisionBox_ = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	if (collisionBox_)
	{
		collisionBox_->SetupAttachment(root_);
		collisionBox_->OnComponentBeginOverlap.AddDynamic(this, &ALevelEndActor::OnBoxOverlapBegin);
	}

	NextLevelName = "Insert Map Name";
}

void ALevelEndActor::OnBoxOverlapBegin(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool fromSweep, const FHitResult& sweepResult)
{
	if (Cast<APlayerCharacter>(otherActor))
	{
		auto nextLevel = NextLevelName.ToString();

		if (!GEngine->MakeSureMapNameIsValid(nextLevel))
		{
			UE_LOG(LogTemp, Error, TEXT("Cannot find map: '%s'."), *nextLevel);

			return;
		}

		UGameplayStatics::OpenLevel(this, NextLevelName);
	}
}