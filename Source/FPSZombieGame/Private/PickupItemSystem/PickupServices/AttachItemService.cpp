// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/PickupServices/AttachItemService.h"

#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\Attachable.h"
#include "StorageSystem\ItemStorage.h"
#include "PickupItemSystem\Pickupable.h"
#include "SwapingSystem\SwapService.h"


bool UAttachItemService::Pickup(IPickupable* itemToPickup, IItemStorage* itemStorage)
{
	if(!itemToPickup || !itemStorage || !itemToPickup->CanPickup())
	{
		return false;
	}

	UActorComponent* storageComponent = Cast<UActorComponent>(itemStorage);
	UActorComponent* pickupableComponent = Cast<UActorComponent>(itemToPickup);

	//Only actor to actor can be attached
	if(	!IsValid(storageComponent) ||
		!IsValid(storageComponent->GetOwner()) ||
		!IsValid(pickupableComponent)||
		!IsValid(pickupableComponent->GetOwner()))
	{
		return false;
	}


	bool added = itemStorage->AddItem(itemToPickup->GetItemData());

	if(!added)
	{
		UItemDataAsset* blockingItem = itemStorage->GetBlockingItem(itemToPickup->GetItemData());

		if(blockingItem && blockingItem->GetSwapService())
		{
			added = blockingItem->GetSwapService()->Swap(blockingItem,itemToPickup->GetItemData());
		}
	}else
	{
		itemToPickup->GetItemData()->CurrentItemStorage = itemStorage->_getUObject();

		itemToPickup->Pickup();
		TArray<UActorComponent*> attachableComponents = pickupableComponent->GetOwner()->GetComponentsByInterface(
			UAttachable::StaticClass());

		for (UActorComponent* AttachableComponent : attachableComponents)
		{
			Cast<IAttachable>(AttachableComponent)->AttachTo( storageComponent->GetOwner());
		}
	}

	return added;
}
