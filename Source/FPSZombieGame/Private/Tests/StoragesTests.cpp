#include "PickupItemSystem\ItemDataAsset.h"
#include "StorageSystem\ItemStorage.h"
#include "StorageSystem\ItemStorageComponent.h"
#include "StorageSystem\ItemStorageTypes\InfinityItemStorage.h"
#include "Tests\TestsStatics.hpp"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddItemToSimpleStorageTest, "Storage.InfinityStorage.Add", BasicBindingTestFlags)

bool FAddItemToSimpleStorageTest::RunTest(const FString& Parameters)
{
	IItemStorage* ItemStorage = NewObject<UInfinityItemStorage>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();

	TestTrue("Adding item to item storage", ItemStorage->AddItem(basicItemData));
	TestTrue("Add nullptr", !ItemStorage->AddItem(nullptr));
	TestTrue("Checking if ItemStorage contain item", ItemStorage->GetItems().Contains(basicItemData));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRemoveItemToSimpleStorageTest, "Storage.InfinityStorage.Remove", BasicBindingTestFlags)

bool FRemoveItemToSimpleStorageTest::RunTest(const FString& Parameters)
{
	IItemStorage* ItemStorage = NewObject<UInfinityItemStorage>();
	IItemStorage* ItemStorage2 = NewObject<UInfinityItemStorage>();
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStorageComponentAddTest, "Storage.Component.Add", BasicBindingTestFlags)
bool FStorageComponentAddTest::RunTest(const FString& Parameters)
{
	UItemStorageComponent* comp = NewObject<UItemStorageComponent>();
	IItemStorage* ItemStorageImp = NewObject<UInfinityItemStorage>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();

	comp->SetItemStorageImplementation(ItemStorageImp);

	TestTrue("Adding item to item storage", comp->AddItem(basicItemData));
	TestTrue("Checking if ItemStorage contain item", comp->GetItems().Contains(basicItemData));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStorageComponentRemoveTest, "Storage.Component.Remove", BasicBindingTestFlags)
bool FStorageComponentRemoveTest::RunTest(const FString& Parameters)
{
	UItemStorageComponent* comp = NewObject<UItemStorageComponent>();
	IItemStorage* ItemStorageImp = NewObject<UInfinityItemStorage>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();

	comp->SetItemStorageImplementation(ItemStorageImp);
	comp->AddItem(basicItemData);
	TestTrue("Removing item from storage with item", comp->RemoveItem(basicItemData));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStorageComponentImplmementationTest, "Storage.Component.ChangeImplementation", BasicBindingTestFlags)
bool FStorageComponentImplmementationTest::RunTest(const FString& Parameters)
{
	UItemStorageComponent* comp = NewObject<UItemStorageComponent>();
	IItemStorage* ItemStorageImp = NewObject<UInfinityItemStorage>();
	IItemStorage* ItemStorageImp2 = NewObject<UInfinityItemStorage>();
	UItemDataAsset* basicItemData = NewObject<UItemDataAsset>();
	ItemStorageImp->AddItem(basicItemData);

	comp->SetItemStorageImplementation(ItemStorageImp);
	comp->SetItemStorageImplementation(ItemStorageImp2);
	TestTrue("Checking if ItemStorageComp contain old items after implementation changed", comp->GetItems().Contains(basicItemData));


	return true;
}
