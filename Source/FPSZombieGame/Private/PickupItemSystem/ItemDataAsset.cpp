// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\PickupService.h"
#include "UsabilitySystem\Usable.h"
#include "SwapingSystem\SwapService.h"

UItemDataAsset::UItemDataAsset()
{
	CurrentItemStorage = {};
	PickupService = {};
	Usable = {};
	SwapService = {};
}

IUsable* UItemDataAsset::GetUsable()
{
	if(!IsValid(Usable.GetObject()))
		Usable = UsableInject.GetDefaultObject();

	return Usable.GetInterface();
}

IPickupService* UItemDataAsset::GetPickupService()
{
	if(!IsValid(PickupService.GetObject()))
		PickupService = PickupServiceInject.GetDefaultObject();

	return PickupService.GetInterface();
}

ISwapService* UItemDataAsset::GetSwapService()
{
	if(!IsValid(SwapService.GetObject()))
		SwapService = SwapServiceInject.GetDefaultObject();

	return SwapService.GetInterface();
}
