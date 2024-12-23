// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structs/PersonSave.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class CODE_D_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	void SaveFactionTable(const UDataTable* _dataTable);
	void LoadFactionTable(UDataTable* _dataTable);
	void SavePersonTable(const UDataTable* _dataTable);
	void LoadPersonTable(UDataTable* _dataTable);
	void SaveCityTable(const UDataTable* _dataTable);
	void LoadCityTable(UDataTable* _dataTable);
	void SavePersonActor(const FName& _name, const FPersonSave& _data);
	const FPersonSave* LoadPersonActor(const FName& _name);
protected:
	UPROPERTY(BlueprintReadWrite)
	TMap<FName, FPersonSave> m_personActor;
	UPROPERTY(BlueprintReadWrite)
	FString m_factionTable;
	UPROPERTY(BlueprintReadWrite)
	FString m_personTable;
	UPROPERTY(BlueprintReadWrite)
	FString m_cityTable;
};
