// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "tHomasUD.generated.h"

/**
 * 
 */
UCLASS()
class THOMAS_API AtHomasUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UThomasWidget> UserWidgetClass;

private:
	UPROPERTY()
	TObjectPtr<UThomasWidget> UserWidget;
};
