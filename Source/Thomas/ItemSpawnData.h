#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnData.generated.h"

USTRUCT()
struct FItemSpawnData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float Rarity;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> ItemType;
};