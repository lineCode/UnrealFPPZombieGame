// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwapService.h"
#include "UObject/NoExportTypes.h"
#include "SwapActorsDropCurrent.generated.h"

class UItemDataAsset;
/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API USwapActorsDropCurrent : public UObject, public ISwapService
{
	GENERATED_BODY()

public:
	virtual bool Swap(UItemDataAsset* MainObject, UItemDataAsset* SwapWith) override;
};
