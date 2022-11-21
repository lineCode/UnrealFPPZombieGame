// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachable.h"
#include "Components/SkeletalMeshComponent.h"
#include "AttachableItemComponent.generated.h"

class UInputMappingContext;
class UItemDataAsset;
class AFPSZombieGameCharacter;
class UInputAction;
/**
 * 
 */
UCLASS()
class FPSZOMBIEGAME_API UAttachableItemComponent : public USkeletalMeshComponent, public IAttachable
{
private:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AFPSZombieGameCharacter> CurrentOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=AttachParams, meta=(AllowPrivateAccess = "true"))
	FString SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> UseMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UItemDataAsset> Item;
public:

	void Setup(UItemDataAsset* Item);

	UAttachableItemComponent();

	void BindActionMapping();

	virtual void AttachTo(AActor* actor) override;

	virtual void DeAttach() override;

	void Use();
};
