// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaPotion.h"
#include "ThomasCharacter.h"

void AManaPotion::Use(AThomasCharacter* Character)
{
	Character->GainMana(ManaGain);
	Destroy();
}
