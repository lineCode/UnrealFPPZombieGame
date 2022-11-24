// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StorageSystem\ItemStorage.h"
#include "UObject/NoExportTypes.h"
#include "InfinityItemStorage.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UInfinityItemStorage : public UObject,public IItemStorage
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<UItemDataAsset*> ownedItems;

public:
	UInfinityItemStorage();

	virtual bool AddItem(UItemDataAsset* ItemToAdd) override;

	virtual bool RemoveItem(UItemDataAsset* ItemToRemove) override;

	virtual TArray<UItemDataAsset*> GetItems() override;

	virtual UItemDataAsset* GetBlockingItem(UItemDataAsset* ItemToAdd) override;
};
