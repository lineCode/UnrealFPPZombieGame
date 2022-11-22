// Fill out your copyright notice in the Description page of Project Settings.


#include "Mocks/ItemMockBuilder.h"
#include "UsabilitySystem\Usable.h"
#include "PickupItemSystem\ItemDataAsset.h"

FItemMockBuilder* FItemMockBuilder::SetUsable(IUsable* usable)
{
	Usable = usable;

	return this;
}

FItemMockBuilder* FItemMockBuilder::SetPickupServie(IPickupService* PickupService)
{
	Service = PickupService;

	return this;
}

UItemDataAsset* FItemMockBuilder::Construct()
{
	UItemDataAsset* itemData =  TMockBuilder::Construct();

	itemData->Usable = Usable->_getUObject();
	itemData->PickupService = Service->_getUObject();

	return itemData;
}
