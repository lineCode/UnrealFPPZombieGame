// Fill out your copyright notice in the Description page of Project Settings.


#include "SwapingSystem/SwapActorsDropCurrent.h"

#include "PickupItemSystem\Attachable.h"
#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\Pickupable.h"
#include "PickupItemSystem\PickupService.h"
#include "StorageSystem\ItemStorage.h"

bool USwapActorsDropCurrent::Swap(UItemDataAsset* MainObject, UItemDataAsset* SwapWith)
{
	if (!MainObject || !SwapWith || !MainObject->ItemInWorld || !SwapWith->ItemInWorld)
		return {};

	IItemStorage* currentItemStorage = MainObject->CurrentItemStorage.GetInterface();
	IAttachable* attachable = Cast<IAttachable>(MainObject->ItemInWorld->FindComponentByInterface<UAttachable>());
	IPickupable* pickupable = Cast<IPickupable>(MainObject->ItemInWorld->FindComponentByInterface<UPickupable>());
	IPickupable* swapPickupable = Cast<IPickupable>(SwapWith->ItemInWorld->FindComponentByInterface<UPickupable>());

	if (!currentItemStorage || !attachable || !pickupable || !swapPickupable)
		return {};

	currentItemStorage->RemoveItem(MainObject);
	MainObject->CurrentItemStorage = nullptr;

	attachable->Detach();

	pickupable->Drop();

	SwapWith->GetPickupService()->
	          Pickup(swapPickupable, currentItemStorage);

	return true;
}
