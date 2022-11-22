// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\PickupService.h"
#include "UsabilitySystem\Usable.h"

UItemDataAsset::UItemDataAsset()
{
	CurrentItemStorage = {};
	PickupService = {};
	Usable = {};
}

IUsable* UItemDataAsset::GetUsable()
{
	if(!IsValid(Usable.GetObject()))
	{
		Usable = NewObject<UObject>(this, UsableInject);
	}

	return Usable.GetInterface();
}

IPickupService* UItemDataAsset::GetPickupService()
{
	if(!IsValid(PickupService.GetObject()))
	{
		PickupService = NewObject<UObject>(this, PickupServiceInject);
	}

	return PickupService.GetInterface();
}
