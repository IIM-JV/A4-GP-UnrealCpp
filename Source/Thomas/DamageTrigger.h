// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTrigger.generated.h"

UCLASS()
class THOMAS_API ADamageTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void OnDealDamage();

public:
	UPROPERTY(EditAnywhere)
	uint32 Damage = 10;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBoxComponent> Box; // == class UBoxComponent*

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UPointLightComponent> Light;

	UPROPERTY(EditAnywhere)
	FLinearColor DefaultColor;

	UPROPERTY(EditAnywhere)
	FLinearColor DetectionColor;

	UPROPERTY()
	FTimerHandle DamageTimer;

	UPROPERTY(EditAnywhere)
	float DamageRate = 0.5f;

private:
	UPROPERTY()
	AActor* ActorInZone = nullptr;
};
