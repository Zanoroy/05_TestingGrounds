// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TIle.generated.h"

UCLASS()
class BLACKCYBORG_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Dynamic Actors")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn, float Radius = 500.0f, float MinScale = 1.f, float MaxScale = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	bool IsEmpty(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector &OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float RndScale);
};
