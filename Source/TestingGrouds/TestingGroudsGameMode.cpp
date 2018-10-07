// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestingGroudsGameMode.h"
#include "TestingGroudsHUD.h"
#include "TestingGroudsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGroudsGameMode::ATestingGroudsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroudsHUD::StaticClass();
}
