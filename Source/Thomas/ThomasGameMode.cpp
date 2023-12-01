// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThomasGameMode.h"
#include "ThomasCharacter.h"
#include "ThomasHUD.h"
#include "UObject/ConstructorHelpers.h"

AThomasGameMode::AThomasGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AThomasHUD::StaticClass();
}
