// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

class FItemMockBuilder;
class IPickupService;
class IItemStorage;
class IUsable;

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

	friend FItemMockBuilder;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "Usable", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> UsableInject;

	UPROPERTY(EditDefaultsOnly, meta=(MustImplement = "PickupService", DisallowedClasses = "ActorComponent"))
	TSubclassOf<UObject> PickupServiceInject;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IUsable> Usable;

	UPROPERTY(VisibleAnywhere)
	TScriptInterface<IPickupService> PickupService;

public:

	UItemDataAsset();

	TScriptInterface<IItemStorage> CurrentItemStorage;

	IUsable* GetUsable();
	IPickupService* GetPickupService();
};
