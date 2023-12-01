// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThomasGameMode.h"
#include "tHomasUD.h"
#include "UObject/ConstructorHelpers.h"

AThomasGameMode::AThomasGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AtHomasUD::StaticClass();
}
