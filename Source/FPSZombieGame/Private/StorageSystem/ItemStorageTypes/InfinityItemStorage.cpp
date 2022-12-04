// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSystem/ItemStorageTypes/InfinityItemStorage.h"

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

	return true;
}

bool UInfinityItemStorage::RemoveItem(UItemDataAsset* ItemToRemove)
{
	if(!IsValid(ItemToRemove) || ownedItems.Remove(ItemToRemove)<=0)
		return false;

	return true;
}

TArray<UItemDataAsset*> UInfinityItemStorage::GetItems()
{
	return ownedItems;
}

UItemDataAsset* UInfinityItemStorage::GetBlockingItem(UItemDataAsset* ItemToAdd)
{
	//Infinity cant have blocking item
	return nullptr;
}
