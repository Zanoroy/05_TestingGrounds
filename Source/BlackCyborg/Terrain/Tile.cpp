// Bruce Quinton - Copywrite 2018

#include "TIle.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	IsEmpty(GetActorLocation(), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	// FMath::RandRange()
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++) {
		float RndScale = FMath::RandRange(MinScale, MaxScale);
		float CheckRadius = MaxScale * Radius;
		FVector SpawnPoint;
		if(FindEmptyLocation(SpawnPoint, CheckRadius))
		{
			float RndRoatation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint, RndRoatation, RndScale);
		}
		else
		{
			// If we couldn't find a location for this actor, send a warning through
			UE_LOG(LogTemp, Warning, TEXT("Unable to place actor: %s"), *ToSpawn->GetName());
		}
	}
}

bool ATile::IsEmpty(FVector Location, float Radius)
{
	FHitResult HitResult;
	FVector GlobalLoaction = ActorToWorld().TransformPosition(Location);

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		GlobalLoaction,
		GlobalLoaction,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));

	// DrawDebugCapsule(GetWorld(), GlobalLoaction, 0, Radius, FQuat::Identity, HasHit ? FColor::Red : FColor::Green, true);

	return !HasHit;
}

bool ATile::FindEmptyLocation(FVector &OutLocation, float Radius)
{
	FVector Min(0, -2000, 0);
	FVector Max(4000, 2000, 0);
	FBox Bounds(Min, Max);
	const int MaxAttempts = 50;

	for (int attempt = 0; attempt < MaxAttempts; attempt++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);
		if (IsEmpty(SpawnPoint, Radius))
		{
			OutLocation = SpawnPoint;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float RndScale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->SetActorRotation(FRotator(0.f, Rotation, 0.f));
	Spawned->SetActorScale3D(FVector(RndScale));
}

