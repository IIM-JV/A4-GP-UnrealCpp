// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellData.generated.h"

UENUM()
enum class SpellType
{
	Distance
};

/**
 * 
 */
UCLASS()
class THOMAS_API USpellData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	SpellType Type;

	UPROPERTY(EditAnywhere)
	int32 ManaCost;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpellActor;

	UPROPERTY(EditAnywhere)
	float Range;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> Animation;
};
