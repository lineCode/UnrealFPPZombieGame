#include "SwapingSystem\SwapActorsDropCurrent.h"
#include "SwapingSystem\SwapService.h"
#include "Tests\TestsStatics.hpp"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSwapAttachedActor, "Swap.AttachedActors", BasicBindingTestFlags)

bool FSwapAttachedActor::RunTest(const FString& Parameters)
{
	UItemDataAsset* item1,*item2;
	AItemActor* itemActor1,*itemActor2;
	AFPSZombieGameCharacter* player;

	GetBasicAttachItemMock(item1,itemActor1);
	GetBasicAttachItemMock(item2,itemActor2);
	GetInfinityStoragePlayerMock(player);
	item1->GetPickupService()->Pickup(itemActor1->GetPickupable(),player->GetItemStorageComponent());

	ISwapService* service = NewObject<USwapActorsDropCurrent>();
	TestTrue("Swap items",service->Swap(item1,item2));

	TestTrue("Previous item is not in inventory",!player->GetItemStorageComponent()->GetItems().Contains(item1));
	TestTrue("Previous item has nullptr to item storage",item1->CurrentItemStorage == nullptr);

	TestTrue("Current item is in inventory",player->GetItemStorageComponent()->GetItems().Contains(item2));
	TestTrue("Current item has ptr to item storage",item2->CurrentItemStorage == player->GetItemStorageComponent());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSwapAttachedActorNullCheck, "Swap.NullCheck", BasicBindingTestFlags)

bool FSwapAttachedActorNullCheck::RunTest(const FString& Parameters)
{
	ISwapService* service = NewObject<USwapActorsDropCurrent>();
	TestTrue("Swap items",!service->Swap(nullptr,nullptr));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSwapAttachedActorNoActor, "Swap.NoActor", BasicBindingTestFlags)

bool FSwapAttachedActorNoActor::RunTest(const FString& Parameters)
{
	UItemDataAsset* item1,*item2;
	AItemActor* itemActor1,*itemActor2;
	AFPSZombieGameCharacter* player;

	GetBasicAttachItemMock(item1,itemActor1);
	GetBasicAttachItemMock(item2,itemActor2);
	GetInfinityStoragePlayerMock(player);

	item1->GetPickupService()->Pickup(itemActor1->GetPickupable(),player->GetItemStorageComponent());

	item1->ItemInWorld = nullptr;
	item2->ItemInWorld = nullptr;

	ISwapService* service = NewObject<USwapActorsDropCurrent>();
	TestTrue("Swap items",!service->Swap(item1,item2));

	return true;
}
