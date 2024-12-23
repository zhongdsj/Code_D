// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DataComponent.h"
#include "CityDataComponent.generated.h"

struct FCityDataStruct;

DECLARE_LOG_CATEGORY_EXTERN(CityDataComponent, Log, All);
/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class CODE_D_API UCityDataComponent : public UDataComponent
{
	GENERATED_BODY()
public:
	UCityDataComponent();
	static FName GetTag();
	FString GetCityName() const;
	virtual FString GetDetails() const override;

protected:
	virtual void BeginPlay() override;

};
