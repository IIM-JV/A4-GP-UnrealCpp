// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "ThomasWidget.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API UThomasWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	float CurrentHealth = 100.f;
	float TargetHealth = CurrentHealth;

	float CurrentMana = 100.f;
	float TargetMana = CurrentMana;

public:
	UFUNCTION()
	void SetTargetHealth(int32 Health);
	
	UFUNCTION()
	void SetTargetMana(int32 Mana);

	UFUNCTION(BlueprintCallable)
	float ComputeHealthPct() const;

	UFUNCTION(BlueprintCallable)
	float ComputeManaPct() const;

	UPROPERTY(EditAnywhere)
	float UpdateSpeed = 10.f;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere)
	float MaxMana = 100.f;
};
