// Fill out your copyright notice in the Description page of Project Settings.


#include "UsabilitySystem/Usabilities/RaycastShooting.h"

#include "Characters\WeaponOwner.h"
#include "DamageSystem\Damageable.h"
#include "DamageSystem\DamageService.h"
#include "Engine\SkeletalMeshSocket.h"
#include "PickupItemSystem\ItemDataAsset.h"

void URaycastShooting::Use(AActor* User)
{
	if (!User)
		return;

	IWeaponOwner* WeaponOwner = Cast<IWeaponOwner>(User);

	if (!WeaponOwner || !WeaponOwner->HasWeapon() || !WeaponOwner->GetWeapon() || !WeaponOwner->GetWeapon()->
		ItemInWorld)
		return;

	UItemDataAsset* Weapon = WeaponOwner->GetWeapon();

	USkeletalMeshComponent* weaponMesh = Cast<USkeletalMeshComponent>(
		Weapon->ItemInWorld->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	if (weaponMesh->DoesSocketExist(TEXT("Muzzle")))
	{
		FTransform weaponMuzzle = weaponMesh->GetSocketTransform("Muzzle");

		UWorld* world = User->GetWorld();
		TArray<FHitResult> hits;
		world->LineTraceMultiByChannel(hits, weaponMuzzle.GetLocation(),
		                               weaponMuzzle.GetLocation() + weaponMuzzle.Rotator().Vector() * 5000,
		                               ECC_GameTraceChannel2);

		if (hits.Num() > 0)
		{
			IDamageService* DamageService = {}; //FIND NEEDED DAMAGE SERVICE
			// DamageService->DealDamage(&hits.Last(), Weapon, 100);
		}

		DrawDebugLine(world, weaponMuzzle.GetLocation(),
		              weaponMuzzle.GetLocation() + weaponMuzzle.Rotator().Vector() * 5000, FColor::Cyan, true, 100);
	}
}
