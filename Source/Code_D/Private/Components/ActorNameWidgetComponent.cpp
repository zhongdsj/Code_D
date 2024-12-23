// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ActorNameWidgetComponent.h"

#include "Components/CityDataComponent.h"
#include "Widgets/ActorInfoViewWidget.h"

void UActorNameWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> components = this->GetOwner()->GetComponentsByTag(UCityDataComponent::StaticClass(), UCityDataComponent::GetTag());
	if(!components.IsEmpty())
	{
		auto component = Cast<UCityDataComponent>(components[0]);
		if(component != nullptr)
		{
			auto widget = Cast<UActorInfoViewWidget>(this->GetWidget());
			if(widget != nullptr)
			{
				widget->SetText(FText::FromString(component->GetCityName()));
			}
		}
	}
}
