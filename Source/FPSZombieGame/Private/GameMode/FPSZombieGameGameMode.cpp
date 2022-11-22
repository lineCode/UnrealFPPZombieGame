// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/FPSZombieGameGameMode.h"
#include "Characters\FPSZombieGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFPSZombieGameGameMode::AFPSZombieGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
