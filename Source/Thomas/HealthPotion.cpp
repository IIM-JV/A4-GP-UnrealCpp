// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "ThomasCharacter.h"

void AHealthPotion::Use(AThomasCharacter* Character)
{
	Character->Heal(HealValue);
	Destroy();
}
