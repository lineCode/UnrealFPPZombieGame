// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/ItemStorageTypes/InfinityItemStorage.h"

#include "PickupItemSystem\ItemDataAsset.h"

UInfinityItemStorage::UInfinityItemStorage()
{
	ownedItems = {};
}

bool UInfinityItemStorage::AddItem(UItemDataAsset* ItemToAdd)
{
	if(!IsValid(ItemToAdd) || ownedItems.Contains(ItemToAdd))
		return false;

	ownedItems.Add(ItemToAdd);
	ItemStorageUpdated.Broadcast(this);

	return true;
}

bool UInfinityItemStorage::RemoveItem(UItemDataAsset* ItemToRemove)
{
	if(!IsValid(ItemToRemove) || ownedItems.Remove(ItemToRemove)<=0)
		return false;

	ItemStorageUpdated.Broadcast(this);

	return true;
}

TArray<UItemDataAsset*> UInfinityItemStorage::GetItems()
{
	return ownedItems;
}
