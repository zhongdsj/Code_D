// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BattleAnimation.generated.h"

class AWorldPersonCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class CODE_D_API UBattleAnimation : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float _deltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<APawn> m_pawn = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float m_speed = 0;

	UPROPERTY(BlueprintReadOnly)
	FVector m_velocity = {};

	UPROPERTY(BlueprintReadOnly)
	FVector m_forward = {};

	UPROPERTY(BlueprintReadOnly)
	bool m_falling = false;

	UPROPERTY(BlueprintReadOnly)
	bool m_jumping = false;

	UPROPERTY(BlueprintReadOnly)
	FRotator m_look = {};

	UPROPERTY(BlueprintReadOnly)
	bool m_oneHandWeapon = false;

private:
	void UpdateSpeed();

	void UpdateVelocity();

	void UpdateFalling();

	void UpdateForward();

	void UpdateJumping();

	void UpdateLook();

	void UpdateWeaponState();
};
