﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DataComponent.h"
#include "PersonDataComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODE_D_API UPersonDataComponent : public UDataComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPersonDataComponent();
	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;

	virtual FString GetDetails() const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
