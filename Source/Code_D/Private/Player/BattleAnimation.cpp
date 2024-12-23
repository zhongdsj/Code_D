// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BattleAnimation.h"

#include "Components/BattleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/BattleCharacter.h"

void UBattleAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	this->m_pawn = TryGetPawnOwner();
}

void UBattleAnimation::NativeUpdateAnimation(float _deltaSeconds)
{
	Super::NativeUpdateAnimation(_deltaSeconds);
	if(!this->m_pawn.IsValid())
	{
		return;
	}
	UpdateWeaponState();
	UpdateLook();
	UpdateJumping();
	UpdateForward();
	UpdateFalling();
	UpdateVelocity();
	UpdateSpeed();
}

void UBattleAnimation::UpdateSpeed()
{
	this->m_speed = UKismetMathLibrary::VSizeXY(this->m_velocity);
}

void UBattleAnimation::UpdateVelocity()
{
	this->m_velocity = this->m_pawn->GetRootComponent()->GetComponentVelocity();
}

void UBattleAnimation::UpdateFalling()
{
	this->m_falling = this->m_pawn->GetMovementComponent()->IsFalling();
}

void UBattleAnimation::UpdateForward()
{
	this->m_forward = this->m_pawn->GetActorForwardVector();
}

void UBattleAnimation::UpdateJumping()
{
	this->m_jumping = Cast<ACharacter>(this->m_pawn.Get())->bWasJumping;
}

void UBattleAnimation::UpdateLook()
{
	this->m_look = this->m_pawn->GetControlRotation();
}

void UBattleAnimation::UpdateWeaponState()
{
	auto character = Cast<ABattleCharacter>(this->m_pawn.Get());
	if (character != nullptr)
	{
		auto battle_component = character->GetBattleComponent();
		if(battle_component != nullptr)
		{
			this->m_oneHandWeapon = battle_component->HasWeapon();
		}
	}
}
