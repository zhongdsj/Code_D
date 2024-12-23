// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/CityActor.h"

#include "Controllers/WorldPawnController.h"
#include "Enums/EActorMulticastDelegateName.h"
#include "Player/WorldPersonCharacter.h"


DEFINE_LOG_CATEGORY(CityActor);
// Sets default values
ACityActor::ACityActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置根组件
	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("root")));

	this->m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	this->m_mesh->SetupAttachment(this->RootComponent);
}

void ACityActor::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	this->m_hover = true;
	this->Broadcast(EActorMulticastDelegateName::Begin_Cursor_Over);
}

void ACityActor::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	this->m_hover = false;
	this->Broadcast(EActorMulticastDelegateName::End_Cursor_Over);
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("end"));
}

void ACityActor::NotifyActorOnClicked(FKey _buttonPressed)
{
	Super::NotifyActorOnClicked(_buttonPressed);
	this->Broadcast(EActorMulticastDelegateName::On_Click);
	const auto controller = Cast<AWorldPawnController>(this->GetWorld()->GetFirstPlayerController());
	controller->MoveToActor(this, 0);
	// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("tick"));
}

void ACityActor::NotifyActorOnReleased(FKey _buttonReleased)
{
	Super::NotifyActorOnReleased(_buttonReleased);
	this->Broadcast(EActorMulticastDelegateName::On_Release);
}

bool ACityActor::IsCheck() const
{
	return this->m_check;
}

void ACityActor::Check(const bool _check)
{
	this->m_check = _check;
	this->Broadcast(this->m_check ? EActorMulticastDelegateName::Begin_Check : EActorMulticastDelegateName::End_Check);
}


FMulticastDelegate* ACityActor::MulticastDelegate(const EActorMulticastDelegateName& _name)
{
	auto delegate = this->m_multicastDelegateMap.Find(_name);
	if(delegate == nullptr)
	{
		this->m_multicastDelegateMap.Add(_name, FMulticastDelegate());
	}
	delegate = this->m_multicastDelegateMap.Find(_name);
	return delegate;
}

void ACityActor::Broadcast(const EActorMulticastDelegateName& _name)
{
	FMulticastDelegate* delegate = this->m_multicastDelegateMap.Find(_name);
	if (delegate != nullptr)
	{
		delegate->Broadcast();
	}
}

// Called when the game starts or when spawned
void ACityActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACityActor::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

bool ACityActor::IsHover() const
{
	return this->m_hover;
}
