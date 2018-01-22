// Bruce Quinton - Copywrite 2018

#include "InfiniteGameMode.h"
#include "Engine/World.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteGameMode::AInfiniteGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Actor Pool"));
}

// Called when the game starts or when spawned
void AInfiniteGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AInfiniteGameMode::PopulateBoundsVolumePool()
{
	// Get an Iterator to all "ANavMeshBoundsVolumne" objects within the "World"
	TActorIterator<ANavMeshBoundsVolume> ActorIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	// Loop through each item within the Iterator and populate the list..
	while (ActorIterator)
	{
		AddToPool(*ActorIterator);
		++ActorIterator;
	}
}

void AInfiniteGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("Found bounds item: %s"), *VolumeToAdd->GetName())
	NavMeshBoundsVolumePool->CheckIn(VolumeToAdd);
}

