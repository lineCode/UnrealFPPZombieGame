// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/PickupComponent.h"

#include "ItemDataAsset.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"

UPickupComponent::UPickupComponent()
{
	SphereRadius = 32.f;
}

IPickupService* UPickupComponent::GetPickupService()
{
	return ItemData->GetPickupService();
}

UItemDataAsset* UPickupComponent::GetItemData()
{
	return ItemData;
}

void UPickupComponent::Setup(UItemDataAsset* itemData)
{
	this->ItemData = itemData;
}
