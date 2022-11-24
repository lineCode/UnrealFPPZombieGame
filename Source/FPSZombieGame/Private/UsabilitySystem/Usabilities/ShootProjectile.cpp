// Fill out your copyright notice in the Description page of Project Settings.


#include "UsabilitySystem/Usabilities/ShootProjectile.h"

#include "Characters\FPSZombieGameCharacter.h"
#include "DamageSystem\FPSZombieGameProjectile.h"
#include "Kismet\GameplayStatics.h"

void UShootProjectile::Use(AActor* User)
{
	AFPSZombieGameCharacter* Character = Cast<AFPSZombieGameCharacter>(User);

	if (!Character || !Character->GetController() || !ProjectileClass || !Character->GetWorld())
	{
		return;
	}

	UWorld* World = Character->GetWorld();

	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	const FVector SpawnLocation = Character->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	// Spawn the projectile at the muzzle
	World->SpawnActor<AFPSZombieGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMeshWithSockets()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}
