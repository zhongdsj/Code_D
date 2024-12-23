// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CheckInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCheckInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CODE_D_API ICheckInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool IsCheck() const = 0;
	virtual void Check(const bool _check) = 0;
};
