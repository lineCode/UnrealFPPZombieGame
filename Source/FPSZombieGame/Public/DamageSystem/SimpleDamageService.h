// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "DamageService.h"
#include "UObject/NoExportTypes.h"
#include "SimpleDamageService.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API USimpleDamageService : public UObject, public IDamageService
{
	GENERATED_BODY()

public:

	virtual void DealDamage(FHitResult* hitResult, UItemDataAsset* HitBy, int damage) override;
};
