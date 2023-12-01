// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ItemSpawnData.h"
#include "ItemSpawnerSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API UItemSpawnerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	/** Implement this for initialization of instances of the system */
	void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Implement this for deinitialization of instances of the system */
	void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void SpawnItems();

private:
	TArray<FItemSpawnData> ItemSpawnData;
};
