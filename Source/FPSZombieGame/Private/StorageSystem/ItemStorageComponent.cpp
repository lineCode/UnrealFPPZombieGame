// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageSystem/ItemStorageComponent.h"

#include "Game\ZombieGameInstance.h"
#include "PickupItemSystem\ItemDataAsset.h"
#include "Signals\InventoryUpdatedSignal.h"
#include "StorageSystem\ItemStorageTypes\InfinityItemStorage.h"

// Sets default values for this component's properties
UItemStorageComponent::UItemStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UItemStorageComponent::SetItemStorageImplementation(IItemStorage* Interface)
{
	if(Interface == nullptr)
		return;


	if(ItemStorageImplementation.GetInterface() != nullptr)
	{
		TArray<UItemDataAsset*> itemHeld = GetItems();

		for(UItemDataAsset* item : itemHeld)
			Interface->AddItem(item);

	}

	ItemStorageImplementation = Interface->_getUObject();
	SignalBus->InvokeSignal(NewObject<UInventoryUpdatedSignal>());
}

UItemDataAsset* UItemStorageComponent::GetBlockingItem(UItemDataAsset* ItemToAdd)
{
	if(ItemStorageImplementation->GetItems().Num()>0)
	{
		return ItemStorageImplementation->GetItems()[0];
	}

	return nullptr;
}

// Called when the game starts
void UItemStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	SignalBus = GetWorld()->GetGameInstance<UZombieGameInstance>()->GetSignalBus();

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
	if(ItemStorageImplementation.GetInterface()->GetItems().Num()>0)
	{
		return false;
	}

	bool added = ItemStorageImplementation->AddItem(ItemToAdd);

	if(added)
	{
		InvokeSignal();
	}

	return added;
}

void UItemStorageComponent::InvokeSignal()
{
	UInventoryUpdatedSignal* signal = NewObject<UInventoryUpdatedSignal>();
	signal->ItemStorage = this;
	SignalBus->InvokeSignal(signal);
}

bool UItemStorageComponent::RemoveItem(UItemDataAsset* ItemToRemove)
{
	if(ItemStorageImplementation->RemoveItem(ItemToRemove))
	{
		InvokeSignal();
		return true;
	}

	return false;
}

TArray<UItemDataAsset*> UItemStorageComponent::GetItems()
{
	return ItemStorageImplementation->GetItems();
}
