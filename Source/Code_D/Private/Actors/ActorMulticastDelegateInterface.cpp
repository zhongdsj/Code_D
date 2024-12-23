// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ActorMulticastDelegateInterface.h"

// Add default functionality here for any IActorMulticastDelegateInterface functions that are not pure virtual.
FMulticastDelegate* IActorMulticastDelegateInterface::MulticastDelegate(const EActorMulticastDelegateName& _name)
{
	return nullptr;
}

void IActorMulticastDelegateInterface::Broadcast(const EActorMulticastDelegateName& _name)
{

}
