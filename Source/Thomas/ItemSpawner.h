// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class THOMAS_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> Scene;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBillboardComponent> Bhobbit;
#endif
};
