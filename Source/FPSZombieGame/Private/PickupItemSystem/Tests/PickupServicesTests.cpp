

#include "FPSZombieGameCharacter.h"
#include "ItemActor.h"
#include "ItemDataAsset.h"
#include "Mocks\FPSCharacterMockBuilder.h"
#include "Mocks\ItemMockBuilder.h"
#include "PickupItemSystem\AttachableItemComponent.h"
#include "PickupItemSystem\ItemStorage.h"
#include "PickupItemSystem\ItemStorageComponent.h"
#include "PickupItemSystem\Pickupable.h"
#include "PickupItemSystem\PickupComponent.h"
#include "PickupItemSystem\PickupService.h"
#include "PickupItemSystem\ItemStorageTypes\InfinityItemStorage.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"
#include "PickupItemSystem\Usabilities\NoUse.h"
constexpr auto BasicBindingTestFlags = EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayer, "PickupServices.AttachItem", BasicBindingTestFlags)

bool FAttachItemToPlayer::RunTest(const FString& Parameters)
{

	FItemMockBuilder itemFactory = {};
	UItemDataAsset* mockedItem = itemFactory.
		SetPickupServie(NewObject<UAttachItemService>())
		->SetUsable(NewObject<UNoUse>())
		->Construct();

	FPSCharacterMockBuilder CharacterMockBuilder;
	AFPSZombieGameCharacter* Player = CharacterMockBuilder.SetupItemStorageImplementation(NewObject<UInfinityItemStorage>())->Construct();

	AItemActor* BasicItemActor = NewObject<AItemActor>();
	BasicItemActor->Setup(mockedItem);

	TestTrue("Pickup service",mockedItem->GetPickupService()->Pickup(BasicItemActor->GetPickupable(), Player->GetItemStorageComponent()));

	TestTrue("Player have information about wearing weapon",Player->GetHasRifle());
	TestTrue("Player have weapon in item storage comp",Player->GetItemStorageComponent()->GetItems().Contains(mockedItem));
	TestTrue("Weapon have information about storage",mockedItem->CurrentItemStorage == Player->GetItemStorageComponent());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayerSwap, "PickupServices.SwapItem", BasicBindingTestFlags)

bool FAttachItemToPlayerSwap::RunTest(const FString& Parameters)
{
	return true;
}
