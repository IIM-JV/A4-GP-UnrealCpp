// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ThomasHUD.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API AThomasHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UThomasWidget> WidgetClass;

private:
	UPROPERTY()
	TObjectPtr<class UThomasWidget> Widget;

	UFUNCTION()
	void OnHealthChanged(int32 Health);
};
