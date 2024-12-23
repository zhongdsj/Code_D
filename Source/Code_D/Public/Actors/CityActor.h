// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorMulticastDelegateInterface.h"
#include "CheckInterface.h"
#include "GameFramework/Actor.h"
#include "CityActor.generated.h"

class UBoxComponent;
DECLARE_LOG_CATEGORY_EXTERN(CityActor, Log, All);

UCLASS()
class CODE_D_API ACityActor : public AActor, public IActorMulticastDelegateInterface, public ICheckInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACityActor();

	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
	virtual void NotifyActorOnClicked(FKey _buttonPressed) override;
	virtual void NotifyActorOnReleased(FKey _buttonReleased) override;

	// Called every frame
	virtual void Tick(float _deltaTime) override;

	bool IsHover() const;
	virtual bool IsCheck() const override;
	virtual void Check(const bool _check) override;

	virtual FMulticastDelegate* MulticastDelegate(const EActorMulticastDelegateName& _name) override;
	virtual void Broadcast(const EActorMulticastDelegateName& _name) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> m_mesh = nullptr;

private:

	bool m_check = false;
	bool m_hover = false;

	TMap<EActorMulticastDelegateName, FMulticastDelegate> m_multicastDelegateMap;
};
