// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Logging/StructuredLog.h"
#include "ThomasCharacter.h"

// Sets default values
ADamageTrigger::ADamageTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultColor = FLinearColor(0.f, 1.f, 0.f);
	DetectionColor = FLinearColor(1.f, 0.f, 0.f);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Box->ShapeColor = DefaultColor.ToFColor(true);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Box);
	Light->SetLightColor(DefaultColor);

	RootComponent = Box;
}

// Called when the game starts or when spawned
void ADamageTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ADamageTrigger::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ADamageTrigger::OnEndOverlap);
}

void ADamageTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UDamageableInterface>())
	{
		return;
	}

	Light->SetLightColor(DetectionColor);

	ActorInZone = OtherActor;
	GetWorldTimerManager().SetTimer(DamageTimer, this, &ADamageTrigger::OnDealDamage, DamageRate, true, 0.f);
}

void ADamageTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("OnEndOverlap"));

	ActorInZone = nullptr;
	Light->SetLightColor(DefaultColor);
	GetWorldTimerManager().ClearTimer(DamageTimer);
}

#if WITH_EDITOR
void ADamageTrigger::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ADamageTrigger, DefaultColor))
	{
		Light->SetLightColor(DefaultColor);
	}
}
#endif

void ADamageTrigger::OnDealDamage()
{
	if (!ActorInZone)
	{
		return;
	}

	IDamageableInterface* Damageable = Cast<IDamageableInterface>(ActorInZone);
	check(Damageable);

	Damageable->Damage(Damage);
}
