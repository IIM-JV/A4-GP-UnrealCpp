// Fill out your copyright notice in the Description page of Project Settings.


#include "ThomasHUD.h"
#include "ThomasCharacter.h"
#include "ThomasWidget.h"
#include "Kismet/GameplayStatics.h"

void AThomasHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		Widget = CreateWidget<UThomasWidget>(GetWorld(), WidgetClass);
		Widget->AddToViewport();

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		AThomasCharacter* Character = Cast<AThomasCharacter>(PlayerPawn);
		if (Character)
		{
			Character->OnHealthChanged.AddDynamic(this, &AThomasHUD::OnHealthChanged);
		}
	}
}

void AThomasHUD::OnHealthChanged(int32 Health)
{
	if (Widget)
		Widget->HealthPct = Health / 100.f;
}
