// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/WeaponAnimationEnum.h"
#include "Enums/WeaponAttackDirection.h"
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

	void BattleDirectionChange(const FVector2D& _input);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void onEmptyHanded() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnBattleDirectionChange() const;

	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "attackDirection", ToolTip = "朝向enum"))
	EWeaponAttackDirection m_attackDirection = EWeaponAttackDirection::Null;
private:

	TSoftObjectPtr<AWeaponActor> m_weapon = nullptr;

	FOnMontageBlendingOutStarted m_attackReadyMontageBlendingOut;

	bool m_attackReady = false;

	UPROPERTY(EditDefaultsOnly, Category = "Data", meta = (DisplayName = "battle direction change threshold value", ToolTip = "朝向修改阈值"))
	float m_battleDirectionChangeThresholdValue = 0.05f;


	void OnAttackReadyMontageBlendingOut(UAnimMontage* _montage, bool _interrupted);
};
