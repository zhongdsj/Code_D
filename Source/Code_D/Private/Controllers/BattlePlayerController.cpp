// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BattlePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/BattleCharacter.h"

DEFINE_LOG_CATEGORY(BattlePlayerController);

ABattleCharacter* ABattlePlayerController::GetBattleCharacter() const
{
	auto pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController pawn nullptr"));
		return nullptr;
	}

	auto character = Cast<ABattleCharacter>(pawn);
	if(character == nullptr)
	{
		UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController pawn not a battleCharacter"));
	}
	return character;
}

void ABattlePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (this->InputComponent == nullptr)
	{
		UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController inputcomponent nullptr, in SetupInputComponent"));
		return;
	}
	const auto enhanced_input_component = CastChecked<UEnhancedInputComponent>(this->InputComponent);
	if (enhanced_input_component == nullptr)
	{
		return;
	}
	enhanced_input_component->BindAction(this->m_gamePlayerMove, ETriggerEvent::Triggered, this, &ABattlePlayerController::MoveAction);
	enhanced_input_component->BindAction(this->m_gamePlayerLook, ETriggerEvent::Triggered, this, &ABattlePlayerController::LookAction);
	enhanced_input_component->BindAction(this->m_gamePlayerView, ETriggerEvent::Triggered, this, &ABattlePlayerController::ViewAction);
	enhanced_input_component->BindAction(this->m_gamePlayerJump, ETriggerEvent::Triggered, this, &ABattlePlayerController::JumpAction);
	enhanced_input_component->BindAction(this->m_gamePlayerMouseLeft, ETriggerEvent::Triggered, this, &ABattlePlayerController::MouseLeftAction);
}

void ABattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	const auto character = this->GetLocalPlayer();
	if(character != nullptr)
	{
		if(this->m_inputMappingContext != nullptr)
		{
			const auto sub_system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(character);
			if (sub_system != nullptr)
			{
				sub_system->AddMappingContext(this->m_inputMappingContext, 0);
			}else
			{
				UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController inputMappingContext nullptr"));
			}
		}else
		{
			UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController inputMappingContext nullptr"));
		}
		
	}else
	{
		UE_LOG(BattlePlayerController, Warning, TEXT("BattlePlayerController GetLocalPlayer nullptr"));
	}
}

void ABattlePlayerController::MoveAction(const FInputActionValue& _value)
{
	const auto character = this->GetBattleCharacter();
	if(character == nullptr)
	{
		return;
	}

	const auto movement_vector = _value.Get<FVector2D>();
	const FRotator rotation = this->GetControlRotation();
	const FRotator yaw_rotation(0, rotation.Yaw, 0);
	const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
	const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
	character->AddMovementInput(forward_direction, movement_vector.Y);
	character->AddMovementInput(right_direction, movement_vector.X);
}

void ABattlePlayerController::LookAction(const FInputActionValue& _value)
{

	const auto look_vector = _value.Get<FVector2D>() * this->m_mouseSensitivity;

	this->AddYawInput(look_vector.X);
	this->AddPitchInput(-look_vector.Y);

	const auto character = this->GetBattleCharacter();
	if(character == nullptr)
	{
		return;
	}
	// 四向判断
	character->BattleDirectionChange(look_vector);
}

void ABattlePlayerController::ViewAction(const FInputActionValue& _value)
{
	const auto view_value = _value.Get<bool>();
	;
	const auto character = this->GetBattleCharacter();
	if(character == nullptr)
	{
		return;
	}
	character->ChangeSpringArmLength(view_value);
}

void ABattlePlayerController::JumpAction(const FInputActionValue& _value)
{
	const auto jump = _value.Get<bool>();
	const auto character = this->GetBattleCharacter();
	
	if(character == nullptr)
	{
		return;
	}
	jump?character->Jump():character->StopJumping();
}

void ABattlePlayerController::MouseLeftAction(const FInputActionValue& _value)
{

}
