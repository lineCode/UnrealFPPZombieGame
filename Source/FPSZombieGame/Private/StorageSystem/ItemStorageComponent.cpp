// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSystem/ItemStorageComponent.h"

#include "PickupItemSystem\ItemDataAsset.h"
#include "PickupItemSystem\ItemStorageTypes\InfinityItemStorage.h"

// Sets default values for this component's properties
UItemStorageComponent::UItemStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UItemStorageComponent::InvokeEvent(TScriptInterface<IItemStorage> ItemStorage)
{
	ItemStorageUpdated.Broadcast(this);
}

void UItemStorageComponent::SetItemStorageImplementation(IItemStorage* Interface)
{
	if(Interface == nullptr)
		return;


	if(ItemStorageImplementation.GetInterface() != nullptr)
	{
		ItemStorageImplementation->ItemStorageUpdated.RemoveDynamic(this, &UItemStorageComponent::InvokeEvent);
		TArray<UItemDataAsset*> itemHeld = GetItems();

		for(UItemDataAsset* item : itemHeld)
			Interface->AddItem(item);

	}

	ItemStorageImplementation = Interface->_getUObject();
	ItemStorageImplementation->ItemStorageUpdated.AddDynamic(this, &UItemStorageComponent::InvokeEvent);
}

// Called when the game starts
void UItemStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	if(!ItemStorageImplementation)
	{
		SetItemStorageImplementation(Cast<IItemStorage>(NewObject<UObject>(this, ItemStorageInjection)));
	}

	// ...
	
}


// Called every frame
void UItemStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UItemStorageComponent::AddItem(UItemDataAsset* ItemToAdd)
{
	return ItemStorageImplementation->AddItem(ItemToAdd);
}

bool UItemStorageComponent::RemoveItem(UItemDataAsset* ItemToRemove)
{
	return ItemStorageImplementation->RemoveItem(ItemToRemove);
}

TArray<UItemDataAsset*> UItemStorageComponent::GetItems()
{
	return ItemStorageImplementation->GetItems();
}
