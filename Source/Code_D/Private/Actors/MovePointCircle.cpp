// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MovePointCircle.h"
#include "Player/BattleCharacter.h"

// Sets default values
AMovePointCircle::AMovePointCircle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// 设置根组件
	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("root")));

	// 设置定时器
	this->m_timeHandle = new FTimerHandle;

	this->Hide();
}

void AMovePointCircle::SetVisibility(const bool _visibility)
{
	this->GetRootComponent()->SetVisibility(_visibility, true);
	this->SetActorEnableCollision(_visibility);
	this->SetActorTickEnabled(_visibility);
}

// Called when the game starts or when spawned
void AMovePointCircle::BeginPlay()
{
	Super::BeginPlay();
}

void AMovePointCircle::Hide()
{
	this->SetVisibility(false);
}

// Called every frame
void AMovePointCircle::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AMovePointCircle::OverlappingBattleCharacter(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	if(!_otherActor->IsA(ABattleCharacter::StaticClass()))
	{
		return;
	}
	this->SetVisibility(false);
}

void AMovePointCircle::ShowInLocation(const FVector& _location)
{
	this->SetActorLocation(_location + this->m_offset);
	this->SetVisibility(true);
	if(this->m_aliveTime != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(*this->m_timeHandle, this, &AMovePointCircle::Hide, this->m_aliveTime, false);
	}
}

float AMovePointCircle::GetAliveTime() const
{
	return this->m_aliveTime;
}

void AMovePointCircle::EndPlay(const EEndPlayReason::Type _endPlayReason)
{
	Super::EndPlay(_endPlayReason);
	if (this->m_timeHandle != nullptr)
	{
		GetWorldTimerManager().ClearTimer(*this->m_timeHandle);
		delete this->m_timeHandle;
	}
}

