// Bruce Quinton - Copywrite 2018

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

AActor * UActorPool::CheckOut()
{
	if (PoolObjects.Num() == 0)
	{
		return nullptr;
	}

	return PoolObjects.Pop(true);
}

void UActorPool::CheckIn(AActor * ActorToCheckIn)
{
	PoolObjects.Push(ActorToCheckIn);
	// UE_LOG(LogTemp, Warning, TEXT("Item added to pool: %s - Pool Size: %i"), *ActorToCheckIn->GetName(), PoolObjects.Num())
}
