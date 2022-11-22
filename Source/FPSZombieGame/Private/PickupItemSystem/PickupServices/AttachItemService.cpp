// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/PickupServices/AttachItemService.h"

#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\Attachable.h"
#include "StorageSystem\ItemStorage.h"
#include "PickupItemSystem\Pickupable.h"

UActorComponent* storageComponent;

bool UAttachItemService::Pickup(IPickupable* itemToPickup, IItemStorage* itemStorage)
{
	storageComponent = Cast<UActorComponent>(itemStorage);
	UActorComponent* pickupableComponent = Cast<UActorComponent>(itemToPickup);


	//Only actor to actor can be attached
	if(	!IsValid(storageComponent) ||
		!IsValid(storageComponent->GetOwner()) ||
		!IsValid(pickupableComponent)||
		!IsValid(pickupableComponent->GetOwner()))
	{
		return false;
	}

	TArray<UActorComponent*> attachableComponents = pickupableComponent->GetOwner()->GetComponentsByInterface(
		UAttachable::StaticClass());

	itemStorage->AddItem(itemToPickup->GetItemData());
	itemToPickup->GetItemData()->CurrentItemStorage = itemStorage->_getUObject();

	for (UActorComponent* AttachableComponent : attachableComponents)
	{
		Cast<IAttachable>(AttachableComponent)->AttachTo( storageComponent->GetOwner());
	}


	return true;
}
