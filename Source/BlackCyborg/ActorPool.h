// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKCYBORG_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<AActor*>PoolObjects;

public:	
	// Sets default values for this component's properties
	UActorPool();

	AActor* CheckOut();
	void CheckIn(AActor* ActorToCheckIn);
	

};
