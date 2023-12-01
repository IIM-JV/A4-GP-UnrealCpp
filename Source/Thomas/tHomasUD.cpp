// Fill out your copyright notice in the Description page of Project Settings.


#include "tHomasUD.h"
#include "ThomasCharacter.h"
#include "ThomasWidget.h"
#include "Kismet/GameplayStatics.h"

void AtHomasUD::BeginPlay()
{
	AThomasCharacter* Character = Cast<AThomasCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (UserWidgetClass)
	{
		UserWidget = CreateWidget<UThomasWidget>(GetWorld(), UserWidgetClass);
		UserWidget->AddToViewport();

		Character->OnHealthUpdate.AddDynamic(UserWidget, &UThomasWidget::SetTargetHealth);
		//Character->OnHealthUpdate.AddDynamic(UserWidget, &UThomasWidget::SetTargetMana);
	}
}
