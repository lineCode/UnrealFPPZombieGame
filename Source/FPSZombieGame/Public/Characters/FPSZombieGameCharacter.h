// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StorageSystem\ItemStorage.h"
#include "PickupItemSystem\AttachPlace.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "WeaponOwner.h"
#include "FPSZombieGameCharacter.generated.h"
class FPSCharacterMockBuilder;
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UInputMappingContext;
class UItemStorageComponent;
class UInputMappingContext;

UCLASS(config=Game)
class AFPSZombieGameCharacter : public ACharacter, public IAttachPlace, public IWeaponOwner
{
	GENERATED_BODY()

	friend FPSCharacterMockBuilder;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerInventory, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UItemStorageComponent> PlayerItemStorageComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Use Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> UseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	float SearchDistance;
public:
	AFPSZombieGameCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual bool HasWeapon() override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Use();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	UFUNCTION(BlueprintCallable, Category = Player)
	virtual USkeletalMeshComponent* GetMeshWithSockets() { return Mesh1P; }

	UFUNCTION(BlueprintCallable, Category = Player)
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	IItemStorage* GetItemStorageComponent();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual UItemDataAsset* GetWeapon() override;
};
