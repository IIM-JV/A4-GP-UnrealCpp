// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ThomasWidget.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API UThomasWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	float GetHealthBarPct() const;

	UFUNCTION(BlueprintCallable)
	float GetManaBarPct() const;

	float HealthPct = 1.f;
	float ManaPct = 1.f;
};
