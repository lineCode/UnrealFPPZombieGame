// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStorage.h"
#include "Components/ActorComponent.h"
#include "InfinityItemStorageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSZOMBIEGAME_API UInfinityItemStorageComponent : public UActorComponent, public IItemStorage
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInfinityItemStorageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<UItemDataAsset*> ownedItems;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool AddItem(UItemDataAsset* ItemToAdd) override;

	virtual bool RemoveItem(UItemDataAsset* ItemToRemove) override;

	virtual TArray<UItemDataAsset*> GetItems() override;
		
};
