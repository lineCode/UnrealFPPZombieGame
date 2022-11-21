// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemDataAsset.h"
#include "ItemActor.generated.h"

class IPickupable;
class UPickupComponent;
class UAttachableItemComponent;
UCLASS()
class FPSZOMBIEGAME_API AItemActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAttachableItemComponent> AttachableItemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPickupComponent> PickupComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UItemDataAsset> ItemDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UItemDataAsset> ItemDataAssetInjection;

public:	
	// Sets default values for this actor's properties
	AItemActor();
	void Setup(UItemDataAsset* asset);
	IPickupable* GetPickupable();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
