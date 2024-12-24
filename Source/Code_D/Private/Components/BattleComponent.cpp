// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BattleComponent.h"
#include "Actors/WeaponActor.h"
#include "Enums/WeaponAttackDirection.h"
#include "GameFramework/Character.h"
#include "Player/BattleCharacter.h"

// Sets default values for this component's properties
UBattleComponent::UBattleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	m_attackReadyMontageBlendingOut.BindUObject(this, &UBattleComponent::OnAttackReadyMontageBlendingOut);
}

// Called when the game starts
void UBattleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBattleComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

void UBattleComponent::OnAttackReadyMontageBlendingOut(UAnimMontage* _montage, bool _interrupted)
{
	this->m_attackReady = true;
	auto character = m_weapon->GetOwnerCharacter();
	if(character != nullptr)
	{
		auto mesh = character->GetMesh();
		UAnimInstance* anim_instance = (mesh) ? mesh->GetAnimInstance() : nullptr;
		if(anim_instance != nullptr)
		{
			// anim_instance->Montage_Pause(_montage);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("ready"));
}

bool UBattleComponent::HasWeapon() const
{
	return this->m_weapon.Get() == nullptr;
}

void UBattleComponent::SetWeapon(AWeaponActor* _weapon)
{
	this->m_weapon = _weapon;
}

void UBattleComponent::AttackReady(EWeaponAnimationEnum _direction)
{

	if (this->m_weapon != nullptr)
	{
		UAnimMontage* anim_montage = this->m_weapon->FindAnimation(_direction);
		auto character = m_weapon->GetOwnerCharacter();
		if (character != nullptr)
		{
			auto mesh = character->GetMesh();
			UAnimInstance* anim_instance = (mesh) ? mesh->GetAnimInstance() : nullptr;
			character->PlayAnimMontage(anim_montage);
			if (anim_montage && anim_instance)
			{
				float const duration = anim_instance->Montage_Play(anim_montage, 1.0f);
				if (duration > 0.f)
				{
					anim_instance->Montage_SetBlendingOutDelegate(m_attackReadyMontageBlendingOut, anim_montage);
				}
			}

		}
	}
}

bool UBattleComponent::AttackReady() const
{
	return this->m_attackReady;
}

void UBattleComponent::BattleDirectionChange(const FVector2D& _input)
{
	if (_input.X > this->m_battleDirectionChangeThresholdValue)
	{
		this->m_attackDirection = EWeaponAttackDirection::Right;
	}
	else if (_input.X < -this->m_battleDirectionChangeThresholdValue)
	{
		this->m_attackDirection = EWeaponAttackDirection::Left;
	}
	else if (_input.Y > this->m_battleDirectionChangeThresholdValue)
	{
		this->m_attackDirection = EWeaponAttackDirection::Up;
	}
	else if (_input.Y < -this->m_battleDirectionChangeThresholdValue)
	{
		this->m_attackDirection = EWeaponAttackDirection::Down;
	}
	this->OnBattleDirectionChange();
}
