// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ActorNameWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class CODE_D_API UActorNameWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
