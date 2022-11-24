// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MockBuilder.h"
#include "UsabilitySystem\Usable.h"

class UItemDataAsset;
class ISwapService;
class IPickupService;

/**
 * 
 */

class FPSZOMBIEGAME_API FItemMockBuilder: public TMockBuilder<UItemDataAsset>
{
	IUsable* Usable = {};
	IPickupService* Service = {};
	ISwapService* SwapService = {};

public:
	FItemMockBuilder* SetUsable(IUsable* Usable);
	FItemMockBuilder* SetPickupServie(IPickupService* PickupService);
	FItemMockBuilder* SetSwapService(ISwapService* SwapService);

	virtual UItemDataAsset* Construct() override;
};
