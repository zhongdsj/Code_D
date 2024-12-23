// Fill out your copyright notice in the Description page of Project Settings.


#include "Player//WorldPersonCharacter.h"

#include "MySaveGame.h"
#include "Components/CapsuleComponent.h"
#include "Components/PersonDataComponent.h"
#include "Controllers/WorldPawnController.h"
#include "Enums/EActorMulticastDelegateName.h"
//#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWorldPersonCharacter::AWorldPersonCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	// this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AWorldPersonCharacter::OnCapsule);
	this->GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AWorldPersonCharacter::OnCapsule);
}

void AWorldPersonCharacter::OnCapsule(UPrimitiveComponent* _hitComponent, AActor* _otherActor,
                                      UPrimitiveComponent* _otherComp, FVector _normalImpulse, const FHitResult& _hit)
{
	AWorldPersonCharacter* other = Cast<AWorldPersonCharacter>(_otherActor);
	if(other != nullptr && this->m_needCallCapsule)
	{
		other->m_needCallCapsule = false;
		other->Check(false);
		// this->Check(false);
	}

	if(this->m_needCallCapsule)
	{
		this->NotifyOnCapsule(other);
	}

	this->m_needCallCapsule = true;
}

// Called every frame
void AWorldPersonCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

// Called to bind functionality to input
void AWorldPersonCharacter::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}

void AWorldPersonCharacter::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	this->Broadcast(EActorMulticastDelegateName::Begin_Cursor_Over);
}

void AWorldPersonCharacter::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	this->Broadcast(EActorMulticastDelegateName::End_Cursor_Over);
}

void AWorldPersonCharacter::NotifyActorOnClicked(FKey _buttonPressed)
{
	Super::NotifyActorOnClicked(_buttonPressed);
	this->Broadcast(EActorMulticastDelegateName::On_Click);
	const auto controller =  Cast<AWorldPawnController>(this->GetWorld()->GetFirstPlayerController());
	controller->MoveToActor(this, 0);
}

bool AWorldPersonCharacter::IsCheck() const
{
	return this->m_check;
}

void AWorldPersonCharacter::Check(const bool _check)
{
	this->m_check = _check;
	this->Broadcast(this->m_check ? EActorMulticastDelegateName::Begin_Check : EActorMulticastDelegateName::End_Check);
}

void AWorldPersonCharacter::BeginSpace()
{
	this->Broadcast(EActorMulticastDelegateName::Begin_Space);
}

void AWorldPersonCharacter::EndSpace()
{
	this->Broadcast(EActorMulticastDelegateName::End_Space);
}

void AWorldPersonCharacter::SaveGame(USaveGame* _saveGame)
{
	auto save_game = Cast<UMySaveGame>(_saveGame);
	if(save_game == nullptr)
	{
		return;
	}
	FPersonSave person_save = {};
	person_save.location = this->GetActorLocation();
	person_save.rotation = this->GetActorRotation();
	save_game->SavePersonActor(this->GetPersonHandleName(), person_save);
}

void AWorldPersonCharacter::LoadGame(USaveGame* _saveGame)
{
	auto save_game = Cast<UMySaveGame>(_saveGame);
	if (save_game == nullptr)
	{
		return;
	}
	const FPersonSave* person_save = save_game->LoadPersonActor(this->GetPersonHandleName());
	if(person_save != nullptr)
	{
		this->SetActorLocation(person_save->location);
		this->SetActorRotation(person_save->rotation);
	}
}

FName AWorldPersonCharacter::GetPersonHandleName()
{
	if(this->m_dataName.IsNone())
	{
		auto data_component = Cast<UPersonDataComponent>(this->FindComponentByClass(UPersonDataComponent::StaticClass()));
		this->m_dataName = data_component->GetDataName();
	}
	return this->m_dataName;
}

FMulticastDelegate* AWorldPersonCharacter::MulticastDelegate(const EActorMulticastDelegateName& _name)
{
	auto delegate = this->m_multicastDelegateMap.Find(_name);
	if (delegate == nullptr)
	{
		this->m_multicastDelegateMap.Add(_name, FMulticastDelegate());
	}
	delegate = this->m_multicastDelegateMap.Find(_name);
	return delegate;
}

void AWorldPersonCharacter::Broadcast(const EActorMulticastDelegateName& _name)
{
	FMulticastDelegate* delegate = this->m_multicastDelegateMap.Find(_name);
	if (delegate != nullptr)
	{
		delegate->Broadcast();
	}
}

