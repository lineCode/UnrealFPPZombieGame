// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Signals/Signal.h"
#include "InventoryUpdatedSignal.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UInventoryUpdatedSignal : public USignal
{
	GENERATED_BODY()

public:
	class IItemStorage* ItemStorage;
};

Expose_TNameOf(UInventoryUpdatedSignal);
