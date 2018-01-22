// Bruce Quinton - Copywrite 2018

#include "Mannequin.h"
#include "BlackCyborgProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

		// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Arms"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	FVector Startpoint = Mesh1P->GetSocketLocation(FName("GripPoint"));
	FRotator Rotation = Mesh1P->GetForwardVector().Rotation();
	FActorSpawnParameters SpawnInfo;

	if (GunBluePrint == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character is missing the Gun Blueprint"))
			return;
	}
	else
	{
		Gun = GetWorld()->SpawnActor<AGuardGun>(GunBluePrint,
			Startpoint,
			Rotation,
			SpawnInfo);

		if (IsPlayerControlled())
		{
			//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
			Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}
		else {
			//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		}

		// Gun->SetActorRelativeLocation(GunOffset);
		Gun->AnimInstance3P = GetMesh()->GetAnimInstance();
		Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	}

	if (InputComponent != NULL) {
		// Bind fire event
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

void AMannequin::UnPossessed()
{
	Super::UnPossessed();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if (Gun != NULL)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Call the fire on the gun!!
void AMannequin::PullTrigger()
{
	if(Gun != NULL)
		Gun->OnFire();
}

