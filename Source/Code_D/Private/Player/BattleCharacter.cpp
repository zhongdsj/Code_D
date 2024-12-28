// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BattleCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Components/BattleComponent.h"
// #include "Enums/WeaponAttackDirection.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// 创建相机
	this->m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("player camera"));
	// 创建相机弹簧臂
	this->m_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("camera boom"));

	// 将相机绑定到弹簧臂上
	this->m_cameraComponent->SetupAttachment(this->m_springArmComponent, USpringArmComponent::SocketName);
	this->m_cameraComponent->bUsePawnControlRotation = false;
	
	// 将弹簧臂绑定到角色胶囊体中
	this->m_springArmComponent->SetupAttachment(this->RootComponent);
	// 设置臂长
	this->m_springArmComponent->TargetArmLength = 400.0f;
	//使用pawn控制旋转  这里没起作用是因为蓝图中没有打勾，被覆盖了,重新生成一下蓝图中打了勾
	this->m_springArmComponent->bUsePawnControlRotation = true;

	// 设置circle
	this->m_circle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("circle"));
	this->m_circle->SetCollisionObjectType(ECC_WorldDynamic);
	this->m_circle->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	this->m_circle->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	this->m_circle->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	this->m_circle->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	this->m_circle->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	this->m_circle->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	this->m_circle->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Ignore);
	this->m_circle->SetCollisionResponseToChannel(ECC_Destructible, ECR_Ignore);

	this->m_circle->SetupAttachment(this->RootComponent);
}

void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();
	// 设置circle
	this->m_circle->SetVisibility(false);
	this->m_circle->SetScalarParameterValueOnMaterials("radius", this->m_circleRadius);
	this->m_circle->SetVectorParameterValueOnMaterials("color", FVector(this->m_circleColor));

	// soft ptr
	this->m_battleComponent = this->FindComponentByClass(UBattleComponent::StaticClass());
}

void ABattleCharacter::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	// 需要打开碰撞预设 visibility检测

	this->GetMesh()->SetRenderCustomDepth(true);
}

void ABattleCharacter::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	this->GetMesh()->SetRenderCustomDepth(false);
}

UBattleComponent* ABattleCharacter::GetBattleComponent() const
{
	return this->m_battleComponent.Get();
}

void ABattleCharacter::BattleDirectionChange(const FVector2D& _input) const
{
	if (this->m_battleComponent.IsValid())
	{
		this->m_battleComponent->BattleDirectionChange(_input);
	}
}

void ABattleCharacter::ChangeSpringArmLength(const bool _change) const
{
	this->m_springArmComponent->TargetArmLength = _change ? 200.0f : 400.0f;
}

void ABattleCharacter::UpAttack()
{
	if(this->m_battleComponent != nullptr)
	{
		this->m_battleComponent->AttackReady(EWeaponAnimationEnum::AttackUp);
	}
}

void ABattleCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void ABattleCharacter::BeginHighLight()
{
	if(this->m_showHighLight)
	{
		this->GetMesh()->SetOverlayMaterial(this->m_highLightMaterialInterface);
	}
	if(this->m_showCircle)
	{
		this->m_circle->SetVisibility(true);
	}
	
}

void ABattleCharacter::EndHighLight()
{
	if (this->m_showHighLight)
	{
		this->GetMesh()->SetOverlayMaterial(nullptr);
	}
	if (this->m_showCircle)
	{
		this->m_circle->SetVisibility(false);
	}
}

