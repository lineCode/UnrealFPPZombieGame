// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemStorage.generated.h"

class UItemDataAsset;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemStorage : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemStorageUpdated, TScriptInterface<IItemStorage>, updatedItemStorage);
/**
 * 
 */
class FPSZOMBIEGAME_API IItemStorage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FOnItemStorageUpdated ItemStorageUpdated;
	bool virtual AddItem(UItemDataAsset* ItemToAdd) PURE_VIRTUAL(AddItem, return {};);
	bool virtual RemoveItem(UItemDataAsset* ItemToRemove) PURE_VIRTUAL(RemoveItem, return {};);
	TArray<UItemDataAsset*> virtual GetItems() PURE_VIRTUAL(RemoveItem, return {};);
};
