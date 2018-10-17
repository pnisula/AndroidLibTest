// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AndroidLibTestGameMode.h"
#include "AndroidLibTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAndroidLibTestGameMode::AAndroidLibTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
