// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestingGroudsGameMode.h"
#include "TestingGroudsHUD.h"
#include "UObject/ConstructorHelpers.h"

ATestingGroundsGameMode::ATestingGroundsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/BP_Character"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	HUDClass = ATestingGroudsHUD::StaticClass();
}
