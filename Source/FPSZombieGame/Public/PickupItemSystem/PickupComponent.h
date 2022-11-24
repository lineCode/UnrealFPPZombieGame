// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachable.h"
#include "Pickupable.h"
#include "Components/SphereComponent.h"
#include "PickupComponent.generated.h"

/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UPickupComponent : public USphereComponent, public IPickupable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemDataAsset> ItemData;

public:
	UPickupComponent();

	virtual IPickupService* GetPickupService() override;

	virtual UItemDataAsset* GetItemData() override;

	void Setup(UItemDataAsset* ItemData);

	virtual bool CanPickup() override;

	virtual bool Pickup() override;

	virtual bool Drop() override;
};
