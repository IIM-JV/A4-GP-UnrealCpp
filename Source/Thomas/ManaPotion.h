// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ManaPotion.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API AManaPotion : public AItem
{
	GENERATED_BODY()
	
public:
	void Use(class AThomasCharacter* Character) override;

	UPROPERTY(EditAnywhere)
	int32 ManaGain;
};
