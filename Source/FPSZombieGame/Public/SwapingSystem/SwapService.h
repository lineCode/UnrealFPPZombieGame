// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SwapService.generated.h"
class UItemDataAsset;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USwapService : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSZOMBIEGAME_API ISwapService
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool Swap(UItemDataAsset* MainObject,UItemDataAsset* SwapWith) PURE_VIRTUAL(Swap, return {}; );
};
