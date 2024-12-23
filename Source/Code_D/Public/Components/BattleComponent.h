// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/WeaponAnimationEnum.h"
#include "BattleComponent.generated.h"


class AWeaponActor;
class ABattleCharacter;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CODE_D_API UBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBattleComponent();

	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool HasWeapon() const;

	void SetWeapon(AWeaponActor* _weapon);

	void AttackReady(EWeaponAnimationEnum _direction);

	UFUNCTION(BlueprintCallable)
	bool AttackReady() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TSoftObjectPtr<AWeaponActor> m_weapon = nullptr;

	FOnMontageBlendingOutStarted m_attackReadyMontageBlendingOut;

	bool m_attackReady = false;

	void OnAttackReadyMontageBlendingOut(UAnimMontage* _montage, bool _interrupted);
};
