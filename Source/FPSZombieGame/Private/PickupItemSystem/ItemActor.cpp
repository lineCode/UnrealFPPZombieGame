// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItemSystem\ItemActor.h"

#include "PickupItemSystem\AttachableItemComponent.h"
#include "PickupItemSystem\PickupComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachableItemComponent = CreateDefaultSubobject<UAttachableItemComponent>("AttachableComponent");

	PickupComponent = CreateDefaultSubobject<UPickupComponent>("PickupComponent");
	SetRootComponent(PickupComponent);

	AttachableItemComponent->AttachToComponent(PickupComponent,FAttachmentTransformRules::KeepRelativeTransform);
}

void AItemActor::Setup(UItemDataAsset* asset)
{
	ItemDataAsset = asset;
	AttachableItemComponent->Setup(asset);
	PickupComponent->Setup(asset);
	asset->ItemInWorld=this;
}

IPickupable* AItemActor::GetPickupable()
{
	return Cast<IPickupable>(PickupComponent);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if(ItemDataAssetInjection)
	{
		Setup(NewObject<UItemDataAsset>(this, ItemDataAssetInjection));
	}
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
