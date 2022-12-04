// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ZombieGameInstance.h"

#include "Signals\InventoryUpdatedSignal.h"
#include "Signals\SignalBus.h"


UZombieGameInstance::UZombieGameInstance()
{
	SignalBus = NewObject<USignalBus>();;
	SignalBus->AddSignal<UInventoryUpdatedSignal>();
}

USignalBus* UZombieGameInstance::GetSignalBus()
{
	return SignalBus;
}
