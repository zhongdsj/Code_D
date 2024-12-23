// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CircleComponent.h"

#include "Actors/ActorMulticastDelegateInterface.h"
#include "Actors/CheckInterface.h"
#include "Actors/MovePointCircle.h"
#include "Enums/EActorMulticastDelegateName.h"
#include "Player/WorldPersonCharacter.h"

UCircleComponent::UCircleComponent()
{
	
}

void UCircleComponent::OverlappingBattleCharacter(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1, this->GetWorld()->GetDeltaSeconds(), FColor::Red, TEXT("overlap"));
	if (!_otherActor->IsA(AWorldPersonCharacter::StaticClass()))
	{
		return;
	}
	auto owner = Cast<AMovePointCircle>(this->GetOwner());
	if(owner != nullptr)
	{
		owner->Hide();
	}
}

void UCircleComponent::BeginPlay()
{
	Super::BeginPlay();
	this->EndMouseHover();
	this->SetMobility(EComponentMobility::Type::Stationary);
	this->SetCollisionObjectType(ECC_WorldStatic);
	this->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	this->SetCollisionResponseToChannel(ECC_Destructible, ECR_Overlap);

	if(this->m_overlapHide)
	{
		this->OnComponentBeginOverlap.AddDynamic(this, &UCircleComponent::OverlappingBattleCharacter);
	}
	
	auto owner = Cast<IActorMulticastDelegateInterface>(this->GetOwner());
	if (owner != nullptr)
	{
		owner->MulticastDelegate(EActorMulticastDelegateName::Begin_Cursor_Over)->AddUObject(this, &UCircleComponent::BeginMouseHover);
		owner->MulticastDelegate(EActorMulticastDelegateName::End_Cursor_Over)->AddUObject(this, &UCircleComponent::EndMouseHover);
		owner->MulticastDelegate(EActorMulticastDelegateName::Begin_Space)->AddUObject(this, &UCircleComponent::BeginMouseHover);
		owner->MulticastDelegate(EActorMulticastDelegateName::End_Space)->AddUObject(this, &UCircleComponent::EndMouseHover);
		owner->MulticastDelegate(EActorMulticastDelegateName::End_Check)->AddUObject(this, &UCircleComponent::EndMouseHover);
	}
}

void UCircleComponent::BeginMouseHover()
{
	this->SetVisibility(true);
}

void UCircleComponent::EndMouseHover()
{
	auto owner = Cast<ICheckInterface>(this->GetOwner());
	if(owner != nullptr && owner->IsCheck())
	{
		return;
	}
	this->SetVisibility(false);
}