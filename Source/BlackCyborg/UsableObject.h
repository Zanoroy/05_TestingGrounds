// Bruce Quinton - Copywrite 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "UsableObject.generated.h"

/**
 * 
 */
UCLASS()
class BLACKCYBORG_API AUsableObject : public AStaticMeshActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "RenderCustomDepth")
	int InStencilValue = 1;

public:
	AUsableObject();

	UFUNCTION(BlueprintCallable, Category = "Focus")
	void BeginFocus();

	UFUNCTION(BlueprintCallable, Category = "Focus")
	void EndFocus();

	UFUNCTION(BlueprintCallable, Category = "OnUse")
	void OnUsed();

};
