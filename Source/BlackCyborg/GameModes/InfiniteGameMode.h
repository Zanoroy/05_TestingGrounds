// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "BlackCyborgGameMode.h"
#include "InfiniteGameMode.generated.h"


class UActorPool;
/**
 * 
 */
UCLASS()
class BLACKCYBORG_API AInfiniteGameMode : public ABlackCyborgGameMode
{
	GENERATED_BODY()
public:
	AInfiniteGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bounds Pool")
	UActorPool* NavMeshBoundsVolumePool = nullptr;

private:
	void AddToPool(class ANavMeshBoundsVolume* VolumeToAdd);

};
