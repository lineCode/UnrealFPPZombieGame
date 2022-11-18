#include "ItemDataAsset.h"
#include "PickupItemSystem\InfinityItemStorageComponent.h"
#include "PickupItemSystem\ItemStorage.h"
constexpr auto BasicBindingTestFlags = EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter;

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddItemToSimpleStorageTest, "Storage.InfinityStorage.Add", BasicBindingTestFlags)

bool FAddItemToSimpleStorageTest::RunTest(const FString& Parameters)
{
	IItemStorage* ItemStorage = NewObject<UInfinityItemStorageComponent>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();

	TestTrue("Adding item to item storage", ItemStorage->AddItem(basicItemData));
	TestTrue("Add nullptr", !ItemStorage->AddItem(nullptr));
	TestTrue("Checking if ItemStorage contain item", ItemStorage->GetItems().Contains(basicItemData));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRemoveItemToSimpleStorageTest, "Storage.InfinityStorage.Remove", BasicBindingTestFlags)

bool FRemoveItemToSimpleStorageTest::RunTest(const FString& Parameters)
{
	IItemStorage* ItemStorage = NewObject<UInfinityItemStorageComponent>();
	IItemStorage* ItemStorage2 = NewObject<UInfinityItemStorageComponent>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();
	UItemDataAsset* basicItemData2 = NewObject<UItemDataAsset>();
	ItemStorage2->AddItem(basicItemData2);

	TestTrue("Removing item from empty storage", !ItemStorage->RemoveItem(basicItemData));

	ItemStorage->AddItem(basicItemData);
	TestTrue("Removing item from storage with item", ItemStorage->RemoveItem(basicItemData));

	TestTrue("Removing non existing item", !ItemStorage2->RemoveItem(basicItemData));
	TestTrue("Remove nullptr", !ItemStorage2->RemoveItem(nullptr));
	return true;
}
