// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLACKCYBORG_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrollingComponent();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*>PatrolPoints;

public:
	TArray<AActor*> GetPatrolPoints() const;
	
};
