// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attachable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttachable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPSZOMBIEGAME_API IAttachable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttachTo(AActor* actor) PURE_VIRTUAL(AttachTo );
	virtual void DeAttach() PURE_VIRTUAL(DeAttach );
};
