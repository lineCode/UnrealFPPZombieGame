// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponOwner.generated.h"

class UItemDataAsset;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponOwner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSZOMBIEGAME_API IWeaponOwner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool HasWeapon() PURE_VIRTUAL(HasWeapon, return {}; );
	virtual UItemDataAsset* GetWeapon() PURE_VIRTUAL(GetWeapon, return {}; );

};
