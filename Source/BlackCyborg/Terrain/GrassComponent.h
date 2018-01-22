// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Math/Box.h"
#include "GrassComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BLACKCYBORG_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UGrassComponent();

	UPROPERTY(EditAnywhere, Category = "Spawning")
	FBox SpawningExtent;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	uint32 NumberToSpawn = 4000;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	bool bCluster = false;

private:
	void SpawnMesh();
};
