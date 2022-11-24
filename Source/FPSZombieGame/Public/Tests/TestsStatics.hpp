#pragma once
#include "Characters\FPSZombieGameCharacter.h"
#include "Mocks\FPSCharacterMockBuilder.h"
#include "Mocks\ItemMockBuilder.h"
#include "PickupItemSystem\ItemActor.h"
#include "StorageSystem\ItemStorageTypes\InfinityItemStorage.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"
#include "UsabilitySystem\Usabilities\NoUse.h"


constexpr auto BasicBindingTestFlags = EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;

static void GetBasicAttachItemMock(UItemDataAsset*& mockAsset, AItemActor*& mockItemActor)
{
	FItemMockBuilder itemFactory = {};
	mockAsset = itemFactory.
		SetPickupServie(NewObject<UAttachItemService>())
		->SetUsable(NewObject<UNoUse>())
		->SetSwapService(NewObject<USwapActorsDropCurrent>())
		->Construct();

	mockItemActor = NewObject<AItemActor>();
	mockItemActor->Setup(mockAsset);
}

static void GetInfinityStoragePlayerMock(AFPSZombieGameCharacter*& playerMock)
{
	FPSCharacterMockBuilder CharacterMockBuilder = {};
	playerMock = CharacterMockBuilder.SetupItemStorageImplementation(NewObject<UInfinityItemStorage>())->Construct();
}
