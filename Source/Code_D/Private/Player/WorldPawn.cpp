// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WorldPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AWorldPawn::AWorldPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 设置根组件
	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("root")));

	// 创建相机
	this->m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("player camera"));

	// 位置
	this->m_cameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// 旋转
	this->m_cameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	// 缩放
	this->m_cameraComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	// 绑定
	this->m_cameraComponent->SetupAttachment(this->RootComponent);
	this->m_cameraComponent->bUsePawnControlRotation = true;

	// 创建movement
	this->m_movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("movement"));
	// 绑定
	this->m_movementComponent->SetUpdatedComponent(this->RootComponent);

	// 创建timeline
	this->m_cameraMoveTimeLineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("camera move timeline"));
}

// Called when the game starts or when spawned
void AWorldPawn::BeginPlay()
{
	Super::BeginPlay();
	this->m_cameraComponent->SetFieldOfView(this->m_cameraFov);

	if(this->m_timelineCurve != nullptr)
	{
		FOnTimelineFloatStatic timeline_tick_callback;
		FOnTimelineEventStatic timeline_finish_callback;
		timeline_tick_callback.BindUObject(this, &AWorldPawn::CameraMoveTimelineTickCallBack);
		this->m_cameraMoveTimeLineComponent->AddInterpFloat(this->m_timelineCurve, timeline_tick_callback);
		timeline_finish_callback.BindUObject(this, &AWorldPawn::CameraMoveTimelineFinishCallBack);
		this->m_cameraMoveTimeLineComponent->SetTimelineFinishedFunc(timeline_finish_callback);
	}
}

void AWorldPawn::CameraMoveTimelineTickCallBack(const float _value)
{
	this->SetActorLocation(UKismetMathLibrary::VLerp(this->m_moveFrom, this->m_moveTo, _value));
	/*const FRotator rotation = this->GetControlRotation();
	const FVector forward_direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);
	float value = FMath::Lerp(0.0f, _value, 1.0) * this->m_cameraMove;
	this->AddActorLocalOffset(forward_direction * value);*/
}

void AWorldPawn::CameraMoveTimelineFinishCallBack()
{
	this->m_cameraMove = 0.0f;
}

// Called every frame
void AWorldPawn::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

// Called to bind functionality to input
void AWorldPawn::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}

void AWorldPawn::SetCameraFov(const float _fov)
{
	if(_fov != this->m_cameraFov)
	{
		this->m_cameraFov = _fov;
		this->m_cameraComponent->SetFieldOfView(this->m_cameraFov);
	}
}

void AWorldPawn::CameraMove(const float _value)
{
	const FRotator rotation = this->GetControlRotation();
	const FVector forward_direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);
	this->AddActorLocalOffset(forward_direction * _value);
	// this->m_cameraMove += _value;
	// this->m_cameraMoveTimeLineComponent->PlayFromStart();
}

float AWorldPawn::GetSpaceMovementOffset() const
{
	return this->m_spaceMovementOffset;
}

void AWorldPawn::MoveToLocation(const FVector& _location)
{
	// this->SetActorLocation(_location);
	if(!this->m_cameraMoveTimeLineComponent->IsPlaying())
	{
		this->m_moveFrom = this->GetActorLocation();
		this->m_moveTo = _location;
		const float distance = (this->m_moveTo - this->m_moveFrom).Size();
		if(distance < this->m_distanceThresholdValue)
		{
			this->m_cameraMoveTimeLineComponent->SetPlayRate(this->m_playRateThresholdValue);
		}else
		{
			this->m_cameraMoveTimeLineComponent->SetPlayRate(1);
		}
		this->m_cameraMoveTimeLineComponent->PlayFromStart();
	}
}

