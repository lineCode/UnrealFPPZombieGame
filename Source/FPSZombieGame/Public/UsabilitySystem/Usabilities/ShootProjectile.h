// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsabilitySystem\Usable.h"
#include "UObject/NoExportTypes.h"
#include "ShootProjectile.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable)
class FPSZOMBIEGAME_API UShootProjectile : public UObject, public IUsable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFPSZombieGameProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta=(AllowPrivateAccess = "true"))
	UAnimMontage* FireAnimation;

public:

	virtual void Use(AActor* User) override;
};
