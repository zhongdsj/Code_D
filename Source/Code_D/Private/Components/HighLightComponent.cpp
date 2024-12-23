// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HighLightComponent.h"

#include "Actors/ActorMulticastDelegateInterface.h"
#include "Actors/CheckInterface.h"
#include "Enums/EActorMulticastDelegateName.h"

DEFINE_LOG_CATEGORY(HighLightComponent);

// Sets default values for this component's properties
UHighLightComponent::UHighLightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHighLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto owner = Cast<IActorMulticastDelegateInterface>(this->GetOwner());
	if(owner == nullptr)
	{
		UE_LOG(HighLightComponent, Error, TEXT("need actor is a IActorMulticastDelegateInterface"));
		return;
	}

	owner->MulticastDelegate(EActorMulticastDelegateName::Begin_Cursor_Over)->AddUObject(this, &UHighLightComponent::BeginMouseHover);
	owner->MulticastDelegate(EActorMulticastDelegateName::End_Cursor_Over)->AddUObject(this, &UHighLightComponent::EndMouseHover);
	owner->MulticastDelegate(EActorMulticastDelegateName::Begin_Space)->AddUObject(this, &UHighLightComponent::BeginMouseHover);
	owner->MulticastDelegate(EActorMulticastDelegateName::End_Space)->AddUObject(this, &UHighLightComponent::EndMouseHover);
	owner->MulticastDelegate(EActorMulticastDelegateName::End_Check)->AddUObject(this, &UHighLightComponent::EndMouseHover);

	if(this->m_highLightMeshName.IsEmpty())
	{
		UE_LOG(HighLightComponent, Log, TEXT("high light mesh name is empty"));
	}else
	{
		TArray<TObjectPtr<USceneComponent>> components = this->GetOwner()->GetRootComponent()->GetAttachChildren();
		for (const auto component : components)
		{
			if (component->GetFName().GetPlainNameString().Compare(this->m_highLightMeshName) == 0)
			{
				this->m_mesh = Cast<UMeshComponent>(component);
				break;
			}
		}
		if (this->m_mesh == nullptr)
		{
			for (const auto component : components)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, component->GetFName().GetPlainNameString());
			}
			UE_LOG(HighLightComponent, Warning, TEXT("mesh nullptr, check high light mesh name"));
		}
	}

	this->HighLight(false);
}

void UHighLightComponent::BeginMouseHover() const
{
	if(this->m_mesh != nullptr)
	{
		this->HighLight(true);
	}
}

void UHighLightComponent::EndMouseHover() const
{
	if(this->m_mesh != nullptr)
	{
		auto owner = Cast<ICheckInterface>(this->GetOwner());
		if(owner != nullptr && owner->IsCheck())
		{
			return;
		}
		this->HighLight(false);
	}
}

void UHighLightComponent::HighLight(const bool _show) const
{
	if(this->m_mesh != nullptr)
	{
		this->m_mesh->SetOverlayMaterial(_show ? this->m_highLightMaterialInterface : nullptr);
		this->m_mesh->SetRenderCustomDepth(_show);
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("no mesh"));
	}
	
}


// Called every frame
void UHighLightComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

