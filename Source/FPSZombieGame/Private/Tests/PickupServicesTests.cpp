

#include "Characters\FPSZombieGameCharacter.h"
#include "PickupItemSystem\ItemActor.h"
#include "PickupItemSystem\ItemDataAsset.h"
#include "Mocks\FPSCharacterMockBuilder.h"
#include "Mocks\ItemMockBuilder.h"
#include "PickupItemSystem\AttachableItemComponent.h"
#include "StorageSystem\ItemStorage.h"
#include "StorageSystem\ItemStorageComponent.h"
#include "PickupItemSystem\Pickupable.h"
#include "PickupItemSystem\PickupComponent.h"
#include "PickupItemSystem\PickupService.h"
#include "PickupItemSystem\ItemStorageTypes\InfinityItemStorage.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"
#include "UsabilitySystem\Usabilities\NoUse.h"
constexpr auto BasicBindingTestFlags = EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;

void GetBasicAttachItemMock(UItemDataAsset*& mockAsset, AItemActor*& mockItemActor)
{
	FItemMockBuilder itemFactory = {};
	mockAsset = itemFactory.
		SetPickupServie(NewObject<UAttachItemService>())
		->SetUsable(NewObject<UNoUse>())
		->Construct();

	mockItemActor = NewObject<AItemActor>();
	mockItemActor->Setup(mockAsset);
}

void GetInfinityStoragePlayerMock(AFPSZombieGameCharacter*& playerMock)
{
	FPSCharacterMockBuilder CharacterMockBuilder = {};
	playerMock = CharacterMockBuilder.SetupItemStorageImplementation(NewObject<UInfinityItemStorage>())->Construct();
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayer, "PickupServices.AttachItem.Wear", BasicBindingTestFlags)

bool FAttachItemToPlayer::RunTest(const FString& Parameters)
{
	UItemDataAsset* ItemDataMock;
	AItemActor* ItemActorMock;
	AFPSZombieGameCharacter* PlayerMock;
	GetBasicAttachItemMock(ItemDataMock,ItemActorMock);
	GetInfinityStoragePlayerMock(PlayerMock);




	TestTrue("Pickup service",ItemDataMock->GetPickupService()->Pickup(ItemActorMock->GetPickupable(), PlayerMock->GetItemStorageComponent()));

	TestTrue("Player have information about wearing weapon",PlayerMock->GetHasRifle());
	TestTrue("Player have weapon in item storage comp",PlayerMock->GetItemStorageComponent()->GetItems().Contains(ItemDataMock));
	TestTrue("Weapon have information about storage",ItemDataMock->CurrentItemStorage == PlayerMock->GetItemStorageComponent());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayerSwap, "PickupServices.AttachItem.Swap", BasicBindingTestFlags)

bool FAttachItemToPlayerSwap::RunTest(const FString& Parameters)
{


	return true;
}
