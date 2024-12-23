// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PersonDataComponent.h"

#include "Structs/FactionDataStruct.h"
#include "Structs/PersonDataStruct.h"

// Sets default values for this component's properties
UPersonDataComponent::UPersonDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPersonDataComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UPersonDataComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

FString UPersonDataComponent::GetDetails() const
{
	FString str;
	if(this->m_data == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("null"));
		return str;
	}
	auto person_data_struct = this->m_data->CastTo<FPersonDataStruct>();
	// str.Append("<Big>").Append(person_data_struct->person_name).Append("</>");
	str.Append(FString::Printf(TEXT("名称 <Data>%s</>"), GetData(person_data_struct->person_name)));
	str.Append(FString::Printf(TEXT("\n所属阵营 <Data>%s</>"), GetData(person_data_struct->faction_data->faction_name)));
	/*str.Append(FString::Printf(TEXT("\n繁荣度 <Data>%.2f</>"), person_data_struct->prosperity));
	str.Append(FString::Printf(TEXT("\n忠诚度 <Data>%.2f</>"), person_data_struct->loyalty));
	str.Append(FString::Printf(TEXT("\n治安度 <Data>%.2f</>"), person_data_struct->security));*/


	return str;
}

