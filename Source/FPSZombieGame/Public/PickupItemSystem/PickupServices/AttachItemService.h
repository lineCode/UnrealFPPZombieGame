// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupItemSystem\PickupService.h"
#include "UObject/NoExportTypes.h"
#include "AttachItemService.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UAttachItemService : public UObject, public IPickupService
{
	GENERATED_BODY()

public:
	virtual bool Pickup(IPickupable* itemToPickup, IItemStorage* itemStorage) override;
};
