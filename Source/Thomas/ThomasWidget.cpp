// Fill out your copyright notice in the Description page of Project Settings.

#include "ThomasWidget.h"

void UThomasWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (TargetHealth > CurrentHealth)
		CurrentHealth = FMath::Min(CurrentHealth + InDeltaTime * UpdateSpeed, TargetHealth);
	else if (TargetHealth < CurrentHealth)
		CurrentHealth = FMath::Max(CurrentHealth - InDeltaTime * UpdateSpeed, TargetHealth);

	if (TargetMana > CurrentMana)
		CurrentMana = FMath::Min(CurrentMana + InDeltaTime * UpdateSpeed, TargetMana);
	else if (TargetMana < CurrentMana)
		CurrentMana = FMath::Max(CurrentMana - InDeltaTime * UpdateSpeed, TargetHealth);
}

void UThomasWidget::SetTargetHealth(int32 Health)
{
	TargetHealth = Health;
}

void UThomasWidget::SetTargetMana(int32 Mana)
{
	TargetMana = Mana;
}

float UThomasWidget::ComputeHealthPct() const
{
	return CurrentHealth / MaxHealth;
}

float UThomasWidget::ComputeManaPct() const
{
	return CurrentMana / MaxMana;
}
