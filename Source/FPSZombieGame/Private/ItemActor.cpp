// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

#include "PickupItemSystem\AttachableItemComponent.h"
#include "PickupItemSystem\PickupComponent.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachableItemComponent = CreateDefaultSubobject<UAttachableItemComponent>("AttachableComponent");
	PickupComponent = CreateDefaultSubobject<UPickupComponent>("PickupComponent");
}

void AItemActor::Setup(UItemDataAsset* asset)
{
	ItemDataAsset = asset;
	AttachableItemComponent->Setup(asset);
	PickupComponent->Setup(asset);
}

IPickupable* AItemActor::GetPickupable()
{
	return Cast<IPickupable>(PickupComponent);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
