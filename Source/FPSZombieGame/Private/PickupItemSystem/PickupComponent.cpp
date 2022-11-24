// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/PickupComponent.h"

#include "PickupItemSystem\ItemDataAsset.h"

UPickupComponent::UPickupComponent()
{
	SphereRadius = {32.f};
	UPrimitiveComponent::SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
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

bool UPickupComponent::CanPickup()
{
	return ItemData->CurrentItemStorage == nullptr;
}

bool UPickupComponent::Pickup()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return true;
}

bool UPickupComponent::Drop()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	return true;
}
