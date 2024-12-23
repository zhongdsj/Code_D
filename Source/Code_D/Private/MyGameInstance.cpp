// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "PlatformFeatures.h"
#include "SaveGameSystem.h"
#include "Structs/FactionDataStruct.h"
#include "Structs/PersonDataStruct.h"

void UMyGameInstance::PreloadContentForURL(FURL _inURL)
{
	Super::PreloadContentForURL(_inURL);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("name: %s"), *_inURL.ToString()));
}

void UMyGameInstance::LoadComplete(const float _loadTime, const FString& _mapName)
{
	Super::LoadComplete(_loadTime, _mapName);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("complete: %s, use time: %f"), *_mapName, _loadTime));
}

void UMyGameInstance::CreateFaction(const FString& _faction_name, FPersonDataStruct* _person) const
{
	if(this->m_factionDataTable == nullptr)
	{
		return;
	}
	FName row_name(*_faction_name);
	auto data = FFactionDataStruct{};
	data.faction_name = _faction_name;
	data.owner_handle = FDataTableRowHandle{};
	data.owner_handle.DataTable = this->m_personDataTable;
	data.owner_handle.RowName = FName(*_person->person_name);
	this->m_factionDataTable->AddRow(row_name, data);
	_person->faction_handle.RowName = row_name;
	_person->Pack();
}

void UMyGameInstance::CreatePerson(const FString& _person_name, FPersonBaseDataStruct* _person_base_data,
                                   const FFactionDataStruct* _faction, const bool _create_player)
{
	FName* row_name = nullptr;
	if (_create_player)
	{
		row_name = new FName("player");
	}
	else
	{
		row_name = new FName(*_person_name);
	}
	/*auto data = FPersonDataStruct(_person_base_data);
	data.person_name = _person_name;
	data.faction_handle = FDataTableRowHandle{};
	data.faction_handle.DataTable = this->m_factionDataTable;
	data.faction_handle.RowName = FName(*_faction->faction_name);
	this->m_personDataTable->AddRow(*row_name, data);
	if(_create_player)
	{
		this->m_personData = this->m_personDataTable->FindRow<FPersonDataStruct>(*row_name, nullptr);
	}*/
	delete row_name;
}

void UMyGameInstance::CreatePlayer()
{
	/*FName row_name = ;
	auto data = FPersonDataStruct();
	this->m_personDataTable->AddRow(row_name, data);*/
	this->m_personData = this->m_personDataTable->FindRow<FPersonDataStruct>(FName("player"), nullptr);
}

void UMyGameInstance::SetPersonName(const FString& _name) const
{
	if(this->m_personData != nullptr)
	{
		this->m_personData->person_name = _name;
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("no ptr"));
	}
	
}

void UMyGameInstance::SetPersonFaction(const FDataTableRowHandle _handle) const
{
	if (this->m_personData != nullptr)
	{
		this->m_personData->faction_handle = _handle;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("no ptr"));
	}
}

TArray<FString> UMyGameInstance::GetSaved()
{
	ISaveGameSystem* save_game_system = IPlatformFeaturesModule::Get().GetSaveGameSystem();
	TArray<FString> save_names;
	save_game_system->GetSaveGameNames(save_names, 0);
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FApp::GetProjectName());
	return save_names;
}

FString UMyGameInstance::GetLoadName() const
{
	return this->m_loadName;
}

void UMyGameInstance::SetLoadName(const FString& _str)
{
	this->m_loadName = _str;
}

UDataTable* UMyGameInstance::GetPersonDataTable() const
{
	return this->m_personDataTable;
}

UDataTable* UMyGameInstance::GetCityDataTable() const
{
	return this->m_cityDataTable;
}

UDataTable* UMyGameInstance::GetFactionDataTable() const
{
	return this->m_factionDataTable;
}