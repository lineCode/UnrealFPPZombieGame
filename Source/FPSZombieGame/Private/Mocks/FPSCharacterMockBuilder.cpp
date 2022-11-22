// Fill out your copyright notice in the Description page of Project Settings.


#include "Mocks/FPSCharacterMockBuilder.h"

#include "StorageSystem\ItemStorageComponent.h"


FPSCharacterMockBuilder* FPSCharacterMockBuilder::SetupItemStorageImplementation(IItemStorage* ItemStorage)
{
	StorageImp = ItemStorage;
	return this;
}

AFPSZombieGameCharacter* FPSCharacterMockBuilder::Construct()
{
	AFPSZombieGameCharacter* character = TMockBuilder::Construct();

	if(StorageImp)
		Cast<UItemStorageComponent>(character->PlayerItemStorageComponent)->SetItemStorageImplementation(StorageImp);

	return character;
}
