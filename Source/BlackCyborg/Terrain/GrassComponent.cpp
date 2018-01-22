// Bruce Quinton - Copywrite 2018

#include "GrassComponent.h"


UGrassComponent::UGrassComponent()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnMesh();
}

void UGrassComponent::SpawnMesh()
{
	// Create "NumberToSpawn" of items using a loop
	for (uint32 i = 0; i < NumberToSpawn; i++)
	{
		// Find random location
		FVector SpawnPoint = FMath::RandPointInBox(SpawningExtent);
		float RndRoatation = FMath::RandRange(-180.f, 180.f);
		FTransform meshInstance(FRotator(0, RndRoatation, 0), SpawnPoint, FVector::OneVector);
		this->AddInstance(meshInstance);
	}
}


