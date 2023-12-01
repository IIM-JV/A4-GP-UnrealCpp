// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawnerSubsystem.h"
#include "Item.h"
#include "ItemSpawner.h"
#include "ThomasSettings.h"
#include "Kismet/GameplayStatics.h"

void UItemSpawnerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Log, TEXT("Initialize"));

	const UThomasSettings* Settings = GetDefault<UThomasSettings>();
	UDataTable* DataTable = Settings->ItemList.LoadSynchronous();
	if (!DataTable)
		return;

	DataTable->ForeachRow<FItemSpawnData>(TEXT("ItemSpawnerSubsystem"), [this](const FName& RowName, const FItemSpawnData& ItemData)
	{
		UE_LOG(LogTemp, Log, TEXT("Item %s"), *RowName.ToString());
		ItemSpawnData.Add(ItemData);
	});
}

void UItemSpawnerSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("Deinitialize"));
}

void UItemSpawnerSubsystem::SpawnItems()
{
	if (ItemSpawnData.IsEmpty())
		return;

	UWorld* World = GetWorld();

	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(World, AItemSpawner::StaticClass(), Spawners);

	for (AActor* Spawner : Spawners)
	{
		AItemSpawner* ItemSpawner = Cast<AItemSpawner>(Spawner);
		check(ItemSpawner);

		FVector Location = Spawner->GetActorLocation();

		int32 Idx = FMath::RandRange(0, ItemSpawnData.Num() - 1);
		World->SpawnActor<AItem>(ItemSpawnData[Idx].ItemType, Location, FRotator{});
	}
}
