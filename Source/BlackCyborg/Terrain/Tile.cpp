// Bruce Quinton - Copywrite 2018

#include "Tile.h"
// #include "GameFramework/Actor.h"
// #include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "ActorPool.h"

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

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (NavMeshBoundsVolume)
	{
		ActorPool->CheckIn(NavMeshBoundsVolume);
	}
	DestoryAttachedActors();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetActorPool(UActorPool * ActorPoolToSet)
{
	ActorPool = ActorPoolToSet;

	PositionNavMeshBoundsVolume();
	NavMeshBoundsVolume;
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = ActorPool->CheckOut();
	if (NavMeshBoundsVolume)
	{
		NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavMeshOffset);
		GetWorld()->GetNavigationSystem()->Build();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Actor Pool exhausted: NavMeshBoundsVolume is a nullptr"))
		return;
	}
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	RandomlyPlace(ToSpawn, MinSpawn, MaxSpawn, Radius, MinScale, MaxScale);
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius)
{
	RandomlyPlace(ToSpawn, MinSpawn, MaxSpawn, Radius, 1, 1);
}

template<class T>
void ATile::RandomlyPlace(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (int i = 0; i < NumberToSpawn; i++) {
		float RndScale = FMath::RandRange(MinScale, MaxScale);
		float CheckRadius = MaxScale * Radius;
		FVector SpawnPoint;
		if (FindEmptyLocation(SpawnPoint, CheckRadius))
		{
			FSpawnPosition SpawnPoisiton;
			SpawnPoisiton.Rotation = FMath::RandRange(-180.f, 180.f);
			SpawnPoisiton.SpawnLocation = SpawnPoint;
			SpawnPoisiton.RndScale = RndScale;

			SpawnItem(ToSpawn, SpawnPoisiton);
		}
		else
		{
			// If we couldn't find a location for this actor, send a warning through
			UE_LOG(LogTemp, Warning, TEXT("Unable to place actor: %s - %s"), *ToSpawn->GetName(), *SpawnPoint.ToString());
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
	for (int attempt = 0; attempt < MaxPlacementAttemptsPerActor; attempt++)
	{
		FVector SpawnPoint = FMath::RandPointInBox(SpawnBounds);
		if (IsEmpty(SpawnPoint, Radius))
		{
			OutLocation = SpawnPoint;
			return true;
		}
	}
	return false;
}

void ATile::SpawnItem(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	
	if (Spawned)
	{
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Spawned->SetActorRelativeLocation(SpawnPosition.SpawnLocation);
		Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.Rotation, 0.f));
		Spawned->SetActorScale3D(FVector(SpawnPosition.RndScale));
	}
	else
	{
		// If we couldn't find a location for this actor, send a warning through
		UE_LOG(LogTemp, Warning, TEXT("Unable to place Actor: %s - %s"), *ToSpawn->GetName(), *SpawnPosition.SpawnLocation.ToString());
	}
}

void ATile::SpawnItem(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition)
{	
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	APawn* Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn, SpawnPosition.SpawnLocation, FRotator(0.f, SpawnPosition.Rotation, 0.f), ActorSpawnParams);
	
	if (Spawned)
	{
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
		Spawned->SpawnDefaultController();
		Spawned->SetActorRelativeLocation(SpawnPosition.SpawnLocation);
		Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.Rotation, 0.f));
		Spawned->SetActorScale3D(FVector(SpawnPosition.RndScale));
		Spawned->Tags.Add(FName("Enemy"));
	}
	else
	{
		// If we couldn't find a location for this actor, send a warning through
		UE_LOG(LogTemp, Warning, TEXT("Unable to place Pawn: %s - %s"), *ToSpawn->GetName(), *SpawnPosition.SpawnLocation.ToString());
	}
}

void ATile::DestoryAttachedActors()
{
	TArray<AActor*> temp;
	GetAttachedActors(temp);
	UE_LOG(LogTemp, Warning, TEXT("Found: %i actors"), temp.Num());

	// auto iterate though all the actors you already have in the TArray
	for (AActor* CActor : temp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroying: %s"), *CActor->GetName());
		CActor->Destroy();
	}
}