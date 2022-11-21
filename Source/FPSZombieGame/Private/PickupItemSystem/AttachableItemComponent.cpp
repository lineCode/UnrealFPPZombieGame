// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/AttachableItemComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSZombieGameCharacter.h"
#include "ItemDataAsset.h"
#include "PickupItemSystem\AttachPlace.h"
#include "PickupItemSystem\Usable.h"

void UAttachableItemComponent::Setup(UItemDataAsset* item)
{
	Item = item;
}

UAttachableItemComponent::UAttachableItemComponent()
{
	SocketName = "GripPoint";
}

void UAttachableItemComponent::BindActionMapping()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(CurrentOwner->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(UseMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &UAttachableItemComponent::Use);
		}
	}
}

void UAttachableItemComponent::AttachTo(AActor* actor)
{
	if (!IsValid(actor))
		return;

	IAttachPlace* place = dynamic_cast<IAttachPlace*>(actor);

	if(!place)
		return;

	CurrentOwner = Cast<AFPSZombieGameCharacter>(actor);

	// Attach the weapon to the First Person Character

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(place->GetMeshWithSockets(), AttachmentRules, FName(SocketName));

	// Set up action bindings
	if(UseMappingContext && UseAction)
	{
		BindActionMapping();
	}

}

void UAttachableItemComponent::DeAttach()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(CurrentOwner->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(UseMappingContext);
		}
	}

	CurrentOwner = nullptr;
}

void UAttachableItemComponent::Use()
{
	if(IsValid(CurrentOwner))
		Item->GetUsable()->Use(CurrentOwner);
}
