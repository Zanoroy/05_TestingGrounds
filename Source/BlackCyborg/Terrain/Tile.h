// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIle.generated.h"

class UActorPool;
USTRUCT()
struct FSpawnPosition
{
	GENERATED_BODY()

		FVector SpawnLocation;
		float Rotation;
		float RndScale;
};

UCLASS()
class BLACKCYBORG_API ATile : public AActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Dynamic Actors")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius = 500.0f, float MinScale = 1.f, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Dynamic AI Pawns")
	void PlaceAIPawn(TSubclassOf<APawn> ToSpawn, int MinSpawn, int MaxSpawn, float Radius = 10.0f);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Actor Pool")
	void SetActorPool(UActorPool* ActorPoolToSet);
	
	UPROPERTY(EditDefaultsOnly, Category = "Actor Pool")
	FVector NavMeshOffset = FVector(2000, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Dynamic Actors")
	int MaxPlacementAttemptsPerActor = 50;

	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Actors")
	FBox SpawnBounds = FBox(FVector(0, -2000, 0), FVector(4000, 2000, 0));

	
private:
	bool IsEmpty(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	void SpawnItem(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);
	void SpawnItem(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	template<class T>
	void RandomlyPlace(TSubclassOf<T> ToSpawn, int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	UActorPool* ActorPool = nullptr;

	AActor* NavMeshBoundsVolume = nullptr;

	void PositionNavMeshBoundsVolume();

};
