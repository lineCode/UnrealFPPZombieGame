// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStorage.h"
#include "Components/ActorComponent.h"
#include "Game\ZombieGameInstance.h"
#include "ItemStorageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSZOMBIEGAME_API UItemStorageComponent : public UActorComponent, public IItemStorage
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TScriptInterface<IItemStorage> ItemStorageImplementation;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "ItemStorage", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> ItemStorageInjection;

	UPROPERTY()
	TObjectPtr<USignalBus> SignalBus;

	virtual void BeginPlay() override;

	void InvokeSignal();

public:

	UItemStorageComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool AddItem(UItemDataAsset* ItemToAdd) override;

	virtual bool RemoveItem(UItemDataAsset* ItemToRemove) override;

	virtual TArray<UItemDataAsset*> GetItems() override;

	//Cheat to change implementation ig
	void SetItemStorageImplementation(IItemStorage* Interface);

	virtual UItemDataAsset* GetBlockingItem(UItemDataAsset* ItemToAdd) override;
};
