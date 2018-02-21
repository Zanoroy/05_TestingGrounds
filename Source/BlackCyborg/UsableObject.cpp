// Bruce Quinton - Copywrite 2018

#include "UsableObject.h"
#include "Components/StaticMeshComponent.h"

AUsableObject::AUsableObject()
{
}

void AUsableObject::BeginFocus()
{
	this->GetStaticMeshComponent()->SetRenderCustomDepth(true);
	this->GetStaticMeshComponent()->SetCustomDepthStencilValue(InStencilValue);
	this->GetStaticMeshComponent()->MarkRenderStateDirty();
	UE_LOG(LogTemp, Warning, TEXT("Start Focus"))
}

void AUsableObject::EndFocus()
{
	this->GetStaticMeshComponent()->SetRenderCustomDepth(false);
	this->GetStaticMeshComponent()->SetCustomDepthStencilValue(InStencilValue);
	this->GetStaticMeshComponent()->MarkRenderStateDirty();
	UE_LOG(LogTemp, Warning, TEXT("End Focus"))
}

void AUsableObject::OnUsed()
{
	if (HasAuthority())
	{
		this->Destroy();
	}
}
