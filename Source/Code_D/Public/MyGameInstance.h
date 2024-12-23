// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class USaveGame;
class UMySaveGame;
struct FPersonBaseDataStruct;
struct FFactionDataStruct;
struct FPersonDataStruct;
/**
 * 
 */
UCLASS()
class CODE_D_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void PreloadContentForURL(FURL _inURL) override;
	virtual void LoadComplete(const float _loadTime, const FString& _mapName) override;

	void CreateFaction(const FString& _faction_name, FPersonDataStruct* _person) const;
	void CreatePerson(const FString& _person_name, FPersonBaseDataStruct* _person_base_data, const FFactionDataStruct* _faction, const bool _create_player = false);

	UFUNCTION(BlueprintCallable)
	void CreatePlayer();

	UFUNCTION(BlueprintCallable)
	void SetPersonName(const FString& _name) const;

	UFUNCTION(BlueprintCallable)
	void SetPersonFaction(const FDataTableRowHandle _handle) const;

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetSaved();

	FString GetLoadName() const;

	UFUNCTION(BlueprintCallable)
	void SetLoadName(const FString& _str);

	UDataTable* GetPersonDataTable() const;
	UDataTable* GetCityDataTable() const;
	UDataTable* GetFactionDataTable() const;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="data table", meta=(DisplayName="person data table", ToolTip="人物数据表"))
	TObjectPtr<UDataTable> m_personDataTable = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "data table", meta = (DisplayName = "city data table", ToolTip = "城池数据表"))
	TObjectPtr<UDataTable> m_cityDataTable = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "data table", meta = (DisplayName = "faction data table", ToolTip = "势力数据表"))
	TObjectPtr<UDataTable> m_factionDataTable = nullptr;

private:
	FPersonDataStruct* m_personData = nullptr;

	FString m_loadName;
};
