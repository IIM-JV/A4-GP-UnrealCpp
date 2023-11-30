// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThomasCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Logging/StructuredLog.h"
#include "Item.h"
#include "SpellData.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AThomasCharacter

AThomasCharacter::AThomasCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Health = 100;
	Mana = 100;
}

void AThomasCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AThomasCharacter::Damage(int32 Dmg)
{
	if (Health <= 0)
	{
		return;
	}

	Health -= Dmg;
	UE_LOGFMT(LogTemplateCharacter, Log, "New health: {0}", Health);
	if (Health <= 0)
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		GetMesh()->SetSimulatePhysics(true);
	}
}

void AThomasCharacter::Heal(int32 Heal)
{
	Health += Heal;
	if (Health > 100)
		Health = 100;

	UE_LOGFMT(LogTemplateCharacter, Log, "New health: {0}", Health);
}

bool AThomasCharacter::ConsumeMana(int32 ManaCost)
{
	if (Mana < ManaCost)
		return false;

	Mana -= ManaCost;
	UE_LOGFMT(LogTemplateCharacter, Log, "New mana: {0}", Mana);

	return true;
}

void AThomasCharacter::GainMana(int32 ManaGain)
{
	Mana += ManaGain;
	if (Mana > 100)
		Mana = 100;

	UE_LOGFMT(LogTemplateCharacter, Log, "New mana: {0}", Mana);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AThomasCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThomasCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThomasCharacter::Look);
	
		// CastSpell
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Triggered, this, &AThomasCharacter::CastSpell);

		EnhancedInputComponent->BindAction(UseItemAction, ETriggerEvent::Triggered, this, &AThomasCharacter::UseItem);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AThomasCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AThomasCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AThomasCharacter::CastSpell()
{
	if (!CurrentSpell)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Spell is null!"));
		return;
	}

	if (!ConsumeMana(CurrentSpell->ManaCost))
		return;

	UWorld* World = GetWorld();
	check(World);

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * CurrentSpell->Range;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, QueryParams);
	if (bHit)
	{
		World->SpawnActor<AActor>(CurrentSpell->SpellActor, HitResult.Location, FRotator{});
	}
}

void AThomasCharacter::UseItem()
{
	UE_LOG(LogTemp, Log, TEXT("UseItem"));

	UWorld* World = GetWorld();
	check(World);

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start + FollowCamera->GetForwardVector() * UseRange;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	FHitResult HitResult;
	bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_PhysicsBody, QueryParams);
	if (bHit)
	{
		AItem* Item = Cast<AItem>(HitResult.GetActor());
		if (!Item)
			return;

		UE_LOGFMT(LogTemp, Log, "Found Item {0}", HitResult.GetActor()->GetName());
		Item->Use(this);
	}
}
