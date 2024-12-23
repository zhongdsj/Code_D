// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

#include "Structs/PersonDataStruct.h"

void UMySaveGame::SaveFactionTable(const UDataTable* _dataTable)
{
	this->m_factionTable = _dataTable->GetTableAsJSON();
}

void UMySaveGame::LoadFactionTable(UDataTable* _dataTable)
{
	_dataTable->CreateTableFromJSONString(this->m_factionTable);
}

void UMySaveGame::SavePersonTable(const UDataTable* _dataTable)
{
	this->m_personTable = _dataTable->GetTableAsJSON();
}

void UMySaveGame::LoadPersonTable(UDataTable* _dataTable)
{
	if(_dataTable != nullptr)
	{
		_dataTable->CreateTableFromJSONString(this->m_personTable);
	}	
}

void UMySaveGame::SaveCityTable(const UDataTable* _dataTable)
{
	this->m_cityTable = _dataTable->GetTableAsJSON();
}

void UMySaveGame::LoadCityTable(UDataTable* _dataTable)
{
	if (_dataTable != nullptr)
	{
		_dataTable->CreateTableFromJSONString(this->m_cityTable);
	}
}

void UMySaveGame::SavePersonActor(const FName& _name, const FPersonSave& _data)
{
	FPersonSave* person_save = this->m_personActor.Find(_name);
	if(person_save == nullptr)
	{
		this->m_personActor.Add(_name, _data);
	}else
	{
		*person_save = _data;
	}
}

const FPersonSave* UMySaveGame::LoadPersonActor(const FName& _name)
{
	return this->m_personActor.Find(_name);
}
