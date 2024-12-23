// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "Components/BattleComponent.h"
#include "Player/BattleCharacter.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->m_weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("weapon");
	this->m_weaponMesh->SetupAttachment(this->RootComponent);
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void AWeaponActor::AttachToCharacter(ABattleCharacter* _character, FName _socketName)
{
	auto mesh = _character->GetMesh();
	auto transform = mesh->GetSocketTransform(_socketName);
	this->AttachToActor(_character, FAttachmentTransformRules::KeepRelativeTransform, _socketName);
	this->AttachToComponent(mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), _socketName);
	this->m_weaponOwner = _character;
	auto battle_component = _character->GetBattleComponent();
	if(battle_component != nullptr)
	{
		battle_component->SetWeapon(this);
	}
}

UAnimMontage* AWeaponActor::FindAnimation(EWeaponAnimationEnum _animationEnum) const
{
	return this->m_weaponAnimations.Find(_animationEnum)->Get();
}

ABattleCharacter* AWeaponActor::GetOwnerCharacter() const
{
	return this->m_weaponOwner.Get();
}
