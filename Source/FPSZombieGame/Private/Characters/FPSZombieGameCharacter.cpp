// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters\FPSZombieGameCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StorageSystem\ItemStorage.h"
#include "StorageSystem\ItemStorageComponent.h"
#include "PickupItemSystem\Pickupable.h"
#include "PickupItemSystem\PickupService.h"


//////////////////////////////////////////////////////////////////////////
// AFPSZombieGameCharacter

AFPSZombieGameCharacter::AFPSZombieGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	SearchDistance = 500;
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	PlayerItemStorageComponent = CreateDefaultSubobject<UItemStorageComponent>(TEXT("PlayerStorageComp"));
}

void AFPSZombieGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPSZombieGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSZombieGameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSZombieGameCharacter::Look);

		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &AFPSZombieGameCharacter::Use);
	}
}

IItemStorage* AFPSZombieGameCharacter::GetItemStorageComponent()
{
	return Cast<IItemStorage>(PlayerItemStorageComponent);
}

UItemDataAsset* AFPSZombieGameCharacter::GetWeapon()
{
	if(HasWeapon())
	{
		return PlayerItemStorageComponent->GetItems()[0];
	}

	return nullptr;
}


void AFPSZombieGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSZombieGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSZombieGameCharacter::Use()
{
	FHitResult hit = {};

	FVector forwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector cameraPos = FirstPersonCameraComponent->GetComponentTransform().GetLocation();
	DrawDebugLine(GetWorld(), cameraPos, cameraPos + (forwardVector * SearchDistance), FColor::Red, true, 5);

	if (GetWorld()->LineTraceSingleByChannel(hit,
	                                         cameraPos,
	                                         cameraPos + (forwardVector * SearchDistance),
	                                         ECC_Visibility))
	{
		if (IPickupable* Pickupable = dynamic_cast<IPickupable*>(hit.Component.Get()))
		{
			Pickupable->GetPickupService()->Pickup(Pickupable,PlayerItemStorageComponent);
		}
	}
}


bool AFPSZombieGameCharacter::HasWeapon()
{
	//TODO: Check if has riffle as main weapon
	//DUMMY CHECK IF ANY ITEM in bp
	return PlayerItemStorageComponent->GetItems().Num() > 0;
}
