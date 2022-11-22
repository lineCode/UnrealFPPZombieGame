// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsabilitySystem\Usable.h"
#include "UObject/NoExportTypes.h"
#include "NoUse.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UNoUse : public UObject, public IUsable
{
	GENERATED_BODY()

public:
	virtual void Use(AActor* User) override;
};
