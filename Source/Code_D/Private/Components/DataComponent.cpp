// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataComponent.h"
#include "Structs/BaseDataStruct.h"

FName UDataComponent::GetTag()
{
	return "detail_data";
}

// Sets default values for this component's properties
UDataComponent::UDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	this->ComponentTags.Add(UDataComponent::GetTag());
	this->bWantsInitializeComponent = true;
}

FName UDataComponent::GetDataName() const
{
	if(this->m_dataHandle.IsNull())
	{
		return FName(NAME_None);
	}else
	{
		return this->m_dataHandle.RowName;
	}
	
}

FString UDataComponent::GetDetails() const
{
	return "no details";
}


// Called when the game starts
void UDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDataComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

void UDataComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if(this->m_data == nullptr && !this->m_dataHandle.IsNull())
	{
		this->m_data = this->m_dataHandle.GetRow<FBaseDataStruct>(nullptr);
		if(this->m_data != nullptr)
		{
			this->m_data->Pack();
		}
	}
}

