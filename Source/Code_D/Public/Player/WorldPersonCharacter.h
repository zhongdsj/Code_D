// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ActorMulticastDelegateInterface.h"
#include "Actors/CheckInterface.h"
#include "Actors/SaveGameInterface.h"
#include "GameFramework/Character.h"
#include "WorldPersonCharacter.generated.h"

UCLASS()
class CODE_D_API AWorldPersonCharacter : public ACharacter, public ICheckInterface, public IActorMulticastDelegateInterface, public ISaveGameInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorldPersonCharacter();

	// Called every frame
	virtual void Tick(float _deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;

	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
	virtual void NotifyActorOnClicked(FKey _buttonPressed) override;

	virtual bool IsCheck() const override;
	virtual void Check(const bool _check) override;

	void BeginSpace();
	void EndSpace();

	virtual void SaveGame(USaveGame* _saveGame) override;

	virtual void LoadGame(USaveGame* _saveGame) override;

	virtual FMulticastDelegate* MulticastDelegate(const EActorMulticastDelegateName& _name) override;
	virtual void Broadcast(const EActorMulticastDelegateName& _name) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NotifyOnCapsule(AActor* _other);

	UFUNCTION()
	void OnCapsule(UPrimitiveComponent* _hitComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpulse, const FHitResult& _hit);

	bool m_needCallCapsule = true;
private:
	UFUNCTION(BlueprintCallable)
	FName GetPersonHandleName();
	TMap<EActorMulticastDelegateName, FMulticastDelegate> m_multicastDelegateMap;
	bool m_check = false;

	FName m_dataName = "None";
};
