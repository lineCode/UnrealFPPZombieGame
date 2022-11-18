// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem/InfinityItemStorageComponent.h"

#include "ItemDataAsset.h"

// Sets default values for this component's properties
UInfinityItemStorageComponent::UInfinityItemStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ownedItems={};
	// ...
}


// Called when the game starts
void UInfinityItemStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInfinityItemStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInfinityItemStorageComponent::AddItem(UItemDataAsset* ItemToAdd)
{
	if(!IsValid(ItemToAdd) || ownedItems.Contains(ItemToAdd))
		return false;

	ownedItems.Add(ItemToAdd);
	ItemStorageUpdated.Broadcast(this);

	return true;
}

bool UInfinityItemStorageComponent::RemoveItem(UItemDataAsset* ItemToRemove)
{
	if(!IsValid(ItemToRemove) || ownedItems.Remove(ItemToRemove)<=0)
		return false;

	ItemStorageUpdated.Broadcast(this);

	return true;
}

TArray<UItemDataAsset*> UInfinityItemStorageComponent::GetItems()
{
	return ownedItems;
}
