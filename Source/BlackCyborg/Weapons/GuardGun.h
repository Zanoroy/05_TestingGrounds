// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GuardGun.generated.h"

UCLASS()
class BLACKCYBORG_API AGuardGun : public AActor
{
	GENERATED_BODY()

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ABlackCyborgProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Gameplay") //BlueprintReadWrite, 
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	uint32 bUsingMotionControllers : 1;


public:	
	// Sets default values for this actor's properties
	AGuardGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void OnFire();

	// UPROPERTY(EditAnywhere, Category = "Gameplay")
	class UAnimInstance* AnimInstance;

	
};
