// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc\TypeContainer.h"
#include "UObject/NoExportTypes.h"
#include "IoC.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UIoC : public UObject
{
	GENERATED_BODY()

public:
	static TTypeContainer<> Container;

};
