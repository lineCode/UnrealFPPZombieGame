// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MockBuilder.h"
#include "PickupItemSystem\PickupService.h"
#include "PickupItemSystem\Usable.h"

class UItemDataAsset;
/**
 * 
 */

class FPSZOMBIEGAME_API FItemMockBuilder: public TMockBuilder<UItemDataAsset>
{
	IUsable* Usable;
	IPickupService* Service;

public:
	FItemMockBuilder* SetUsable(IUsable* Usable);
	FItemMockBuilder* SetPickupServie(IPickupService* PickupService);

	virtual UItemDataAsset* Construct() override;
};
