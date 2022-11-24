

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
#include "StorageSystem\\ItemStorageTypes\InfinityItemStorage.h"
#include "PickupItemSystem\PickupServices\AttachItemService.h"
#include "UsabilitySystem\Usabilities\NoUse.h"
#include "Tests\TestsStatics.hpp"



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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayerNullCheck, "PickupServices.AttachItem.NullCheck", BasicBindingTestFlags)

bool FAttachItemToPlayerNullCheck::RunTest(const FString& Parameters)
{
	IPickupService* service = NewObject<UAttachItemService>();

	TestTrue("all null",!service->Pickup(nullptr,nullptr));
	TestTrue("item pickupable null",!service->Pickup(nullptr,NewObject<UInfinityItemStorage>()));
	TestTrue("Item storage null",!service->Pickup(NewObject<UPickupComponent>(),nullptr));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAttachItemToPlayerSwap, "PickupServices.AttachItem.Swap", BasicBindingTestFlags)

bool FAttachItemToPlayerSwap::RunTest(const FString& Parameters)
{
	UItemDataAsset* ItemDataMock1,*ItemDataMock2;
	AItemActor* ItemActorMock1,*ItemActorMock2;
	AFPSZombieGameCharacter* PlayerMock;

	GetBasicAttachItemMock(ItemDataMock1,ItemActorMock1);
	GetBasicAttachItemMock(ItemDataMock2,ItemActorMock2);
	GetInfinityStoragePlayerMock(PlayerMock);

	ItemDataMock1->GetPickupService()->Pickup(ItemActorMock1->GetPickupable(), PlayerMock->GetItemStorageComponent());

	TestTrue("Swap",	ItemDataMock2->GetPickupService()->Pickup(ItemActorMock2->GetPickupable(), PlayerMock->GetItemStorageComponent()));
	TestTrue("Player have information about wearing weapon",PlayerMock->GetHasRifle());
	TestTrue("Player have new weapon in item storage comp",PlayerMock->GetItemStorageComponent()->GetItems().Contains(ItemDataMock2));

	TestTrue("Player dont have old weapon in item storage comp",!PlayerMock->GetItemStorageComponent()->GetItems().Contains(ItemDataMock1));
	TestTrue("New Weapon have information about storage",ItemDataMock2->CurrentItemStorage == PlayerMock->GetItemStorageComponent());
	TestTrue("Old Weapon dont have information about storage",ItemDataMock1->CurrentItemStorage != PlayerMock->GetItemStorageComponent());

	return true;
}
