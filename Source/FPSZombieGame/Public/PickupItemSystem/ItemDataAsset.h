// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

class ISwapService;
class FItemMockBuilder;
class IPickupService;
class IItemStorage;
class IUsable;

/**
 * 
 */
UCLASS(Blueprintable)
class FPSZOMBIEGAME_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

	friend FItemMockBuilder;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "Usable", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> UsableInject;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "PickupService", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> PickupServiceInject;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "SwapService", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> SwapServiceInject;

	UPROPERTY()
	TScriptInterface<IUsable> Usable;

	UPROPERTY()
	TScriptInterface<IPickupService> PickupService;

	UPROPERTY()
	TScriptInterface<ISwapService> SwapService;

public:

	UItemDataAsset();

	UPROPERTY()
	TScriptInterface<IItemStorage> CurrentItemStorage;

	UPROPERTY(BlueprintReadOnly, Category=Weapon)
	TObjectPtr<AActor> ItemInWorld;
	
	IUsable* GetUsable();
	IPickupService* GetPickupService();
	ISwapService* GetSwapService();
};
