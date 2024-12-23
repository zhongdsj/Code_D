// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CityDataComponent.h"

#include "Structs/CityDataStruct.h"
#include "Structs/PersonDataStruct.h"
#include "Structs/FactionDataStruct.h"

DEFINE_LOG_CATEGORY(CityDataComponent);

FName UCityDataComponent::GetTag()
{
	return "city_name";
}

FString UCityDataComponent::GetCityName() const
{
	FString result;
	if(this->m_data == nullptr)
	{
		return result;
	}
	auto city_data_struct = this->m_data->CastTo<FCityDataStruct>();
	result.Append("<Name>").Append(city_data_struct->city_name).Append("</>");
	return result;
}


UCityDataComponent::UCityDataComponent()
{
	this->ComponentTags.Add(UCityDataComponent::GetTag());
	// this->bWantsInitializeComponent = true;
}

FString UCityDataComponent::GetDetails() const
{
	FString str;
	if(this->m_data == nullptr)
	{
		return str;
	}
	auto city_data_struct = this->m_data->CastTo<FCityDataStruct>();
	str.Append("<Big>").Append(city_data_struct->city_name).Append("</>");
	str.Append(FString::Printf(TEXT("\n所有者 <Data>%s</>"), GetData(city_data_struct->owner_data->person_name)));
	str.Append(FString::Printf(TEXT("\n所属阵营 <Data>%s</>"), GetData(city_data_struct->owner_data->faction_data->faction_name)));
	str.Append(FString::Printf(TEXT("\n繁荣度 <Data>%.2f</>"), city_data_struct->prosperity));
	str.Append(FString::Printf(TEXT("\n忠诚度 <Data>%.2f</>"), city_data_struct->loyalty));
	str.Append(FString::Printf(TEXT("\n治安度 <Data>%.2f</>"), city_data_struct->security));
	return str;
}

void UCityDataComponent::BeginPlay()
{
	Super::BeginPlay();
}
