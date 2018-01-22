// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/GuardGun.h"
#include "Mannequin.generated.h"

UCLASS()
class BLACKCYBORG_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AGuardGun* Gun;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	TSubclassOf<class AGuardGun> GunBluePrint;
	
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void PullTrigger();

	virtual void UnPossessed() override;

};
