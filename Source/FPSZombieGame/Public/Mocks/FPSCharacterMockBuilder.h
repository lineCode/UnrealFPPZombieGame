// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters\FPSZombieGameCharacter.h"
#include "MockBuilder.h"

/**
 * 
 */
class FPSZOMBIEGAME_API FPSCharacterMockBuilder : public TMockBuilder<AFPSZombieGameCharacter>
{
	IItemStorage* StorageImp;

public:

	FPSCharacterMockBuilder* SetupItemStorageImplementation(IItemStorage* ItemStorage);

	virtual AFPSZombieGameCharacter* Construct() override;

};
