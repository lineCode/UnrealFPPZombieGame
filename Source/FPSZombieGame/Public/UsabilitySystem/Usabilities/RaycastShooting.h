// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UsabilitySystem\Usable.h"
#include "RaycastShooting.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class FPSZOMBIEGAME_API URaycastShooting : public UObject, public IUsable
{
	GENERATED_BODY()

public:
	virtual void Use(AActor* User) override;
};
