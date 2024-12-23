// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UIComponent.h"

#include "Actors/ActorMulticastDelegateInterface.h"
#include "Components/DataComponent.h"
#include "Enums/EActorMulticastDelegateName.h"
#include "Controllers/WorldPawnController.h"

DEFINE_LOG_CATEGORY(UIComponent);

// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	auto owner = Cast<IActorMulticastDelegateInterface>(this->GetOwner());
	this->m_dataComponents = this->GetOwner()->GetComponentsByTag(UDataComponent::StaticClass(), UDataComponent::GetTag());
	if(owner != nullptr)
	{
		owner->MulticastDelegate(EActorMulticastDelegateName::Begin_Cursor_Over)->AddUObject(this, &UUIComponent::BeginMouseHover);

		owner->MulticastDelegate(EActorMulticastDelegateName::End_Cursor_Over)->AddUObject(this, &UUIComponent::EndMouseHover);
	}
}

FText UUIComponent::GetText() const
{
	/*FString str = FString::Printf(TEXT("name: %s\nclass: %s"), GetData(this->GetOwner()->GetActorNameOrLabel()), GetData(this->GetOwner()->GetName()));
	return FText::FromString(str);*/
	if (this->m_dataComponents.IsEmpty())
	{
		UE_LOG(UIComponent, Error, TEXT("actor not has dataComponent"));
		return FText::FromString("error");
	}
	FString str;
	for (const auto component : this->m_dataComponents)
	{
		str.Append(Cast<UDataComponent>(component)->GetDetails()).Append("\n");
	}
	str.RemoveFromEnd("\n");
	return FText::FromString(str);
}


// Called every frame
void UUIComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

void UUIComponent::BeginMouseHover()
{
	this->Show();
}

void UUIComponent::EndMouseHover()
{
	this->GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UUIComponent::Hide);
}

void UUIComponent::Show() const
{
	const auto controller = Cast<AWorldPawnController>(this->GetWorld()->GetFirstPlayerController());
	if(controller != nullptr)
	{
		controller->ShowActorInfoView(this->GetText());
	}
}

void UUIComponent::Hide() const
{
	const auto controller = Cast<AWorldPawnController>(this->GetWorld()->GetFirstPlayerController());
	if (controller != nullptr)
	{
		controller->HideActorInfoView();
	}
}

