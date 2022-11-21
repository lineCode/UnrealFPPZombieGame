// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataAsset.h"

#include "PickupItemSystem\PickupService.h"
#include "PickupItemSystem\Usable.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"
#include "PickupItemSystem\Usabilities\NoUse.h"

UItemDataAsset::UItemDataAsset()
{
	CurrentItemStorage = {};
	PickupService = UAttachItemService::StaticClass();
	Usable = UNoUse::StaticClass();
}

IUsable* UItemDataAsset::GetUsable()
{
	if(!IsValid(Usable.GetObject()))
	{
		Usable = NewObject<UObject>(UsableInject);
	}

	return Usable.GetInterface();
}

IPickupService* UItemDataAsset::GetPickupService()
{
	if(!IsValid(PickupService.GetObject()))
	{
		PickupService = NewObject<UObject>(PickupServiceInject);
	}

	return PickupService.GetInterface();
}
