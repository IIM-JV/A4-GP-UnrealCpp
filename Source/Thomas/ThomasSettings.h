// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ThomasSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig)
class THOMAS_API UThomasSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UDataTable> ItemList;
};
