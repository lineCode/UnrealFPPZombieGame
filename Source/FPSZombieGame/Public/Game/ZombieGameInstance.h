// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Misc\TypeContainer.h"
#include "Signals\SignalBus.h"
#include "ZombieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UZombieGameInstance : public UGameInstance
{
	GENERATED_BODY()

	TObjectPtr<USignalBus> SignalBus;
public:

	UZombieGameInstance();

	USignalBus* GetSignalBus();
};
