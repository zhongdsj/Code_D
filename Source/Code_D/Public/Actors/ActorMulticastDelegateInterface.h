// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorMulticastDelegateInterface.generated.h"

enum class EActorMulticastDelegateName : uint8;
DECLARE_MULTICAST_DELEGATE(FMulticastDelegate)
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorMulticastDelegateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CODE_D_API IActorMulticastDelegateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FMulticastDelegate* MulticastDelegate(const EActorMulticastDelegateName& _name);
	virtual void Broadcast(const EActorMulticastDelegateName& _name);
};
