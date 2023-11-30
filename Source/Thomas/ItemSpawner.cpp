// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "Components/BillboardComponent.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

#if WITH_EDITOR
	Bhobbit = CreateDefaultSubobject<UBillboardComponent>(TEXT("Bhobbit"));
	Bhobbit->SetupAttachment(Scene);
#endif

	RootComponent = Scene;
}
