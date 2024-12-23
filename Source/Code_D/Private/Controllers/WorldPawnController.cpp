// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WorldPawnController.h"
#include "Player/WorldPersonCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/MovePointCircle.h"
#include "Player/WorldPawn.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include <Actors/CheckInterface.h>
#include "GameModes/WorldGameMode.h"

DEFINE_LOG_CATEGORY(WordPawnController);

AWorldPawnController::AWorldPawnController()
{
	
}

void AWorldPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(this->InputComponent == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("inputcomponent nullptr, in SetupInputComponent"));
		return;
	}
	const auto enhanced_input_component = CastChecked<UEnhancedInputComponent>(this->InputComponent);
	if (enhanced_input_component == nullptr)
	{
		return;
	}
	enhanced_input_component->BindAction(this->m_moveAction, ETriggerEvent::Triggered, this, &AWorldPawnController::MoveAction);
	enhanced_input_component->BindAction(this->m_mouseMoveAction, ETriggerEvent::Triggered, this, &AWorldPawnController::MouseMoveAction);
	enhanced_input_component->BindAction(this->m_mouseRollAction, ETriggerEvent::Triggered, this, &AWorldPawnController::MouseRollAction);
	enhanced_input_component->BindAction(this->m_mouseClickAction, ETriggerEvent::Started, this, &AWorldPawnController::MouseClickAction);
	enhanced_input_component->BindAction(this->m_spaceAction, ETriggerEvent::Ongoing, this, &AWorldPawnController::SpaceAction);
	enhanced_input_component->BindAction(this->m_spaceAction, ETriggerEvent::Started, this, &AWorldPawnController::SpaceStartAction);
	enhanced_input_component->BindAction(this->m_spaceAction, ETriggerEvent::Completed, this, &AWorldPawnController::SpaceEndAction);
	enhanced_input_component->BindAction(this->m_key1Action, ETriggerEvent::Triggered, this, &AWorldPawnController::Key1Action);
	enhanced_input_component->BindAction(this->m_key2Action, ETriggerEvent::Triggered, this, &AWorldPawnController::Key2Action);
	enhanced_input_component->BindAction(this->m_key3Action, ETriggerEvent::Triggered, this, &AWorldPawnController::Key3Action);
	enhanced_input_component->BindAction(this->m_mouseRight, ETriggerEvent::Started, this, &AWorldPawnController::MouseRightStartAction);
	enhanced_input_component->BindAction(this->m_mouseRight, ETriggerEvent::Completed, this, &AWorldPawnController::MouseRightEndAction);
}

void AWorldPawnController::EndPlay(const EEndPlayReason::Type _endPlayReason)
{
	Super::EndPlay(_endPlayReason);
	if (this->m_movementCharacter != nullptr)
	{
		this->m_movementCharacter->Destroy();
	}
}

void AWorldPawnController::ShowActorInfoView(const FText& _text) const
{
	FVector2D position = {};
	this->GetMousePosition(position.X, position.Y);
	AWorldGameMode* gameMode = Cast<AWorldGameMode>(this->GetWorld()->GetAuthGameMode());
	if(gameMode != nullptr)
	{
		gameMode->ShowActorInfo(_text, position);
	}
}

void AWorldPawnController::HideActorInfoView() const
{
	AWorldGameMode* gameMode = Cast<AWorldGameMode>(this->GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->HideActorInfo();
	}
	// ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(this->GetWorld(), );
}

void AWorldPawnController::MoveToActor(AActor* _actor, const float _radius) const
{
	// bug 朝向问题 仿照UAIBlueprintHelperLibrary::CreateMoveToProxyObject写法解决
	AAIController* movement_controller = this->m_movementCharacter->GetController<AAIController>();
	movement_controller->bAllowStrafe = false;
	// bOrientRotationToMovement;

	movement_controller->MoveToActor(_actor, _radius, true, true, false);
}

void AWorldPawnController::SetMovementCharacter(AWorldPersonCharacter* _movementPersonCharacter)
{
	this->m_movementCharacter = _movementPersonCharacter;
}

void AWorldPawnController::BeginPlay()
{
	Super::BeginPlay();
	const auto player = GetLocalPlayer();
	const auto world = GetWorld();
	if(world == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("world nullptr, in BeginPlay"));
		return;
	}
	if (player == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("player nullptr, in BeginPlay"));
		return;
	}
	if (this->m_inputMappingContext == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("inputMappingContext nullptr, in BeginPlay"));
		return;
	}
	const auto sub_system = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(player);
	if (sub_system == nullptr)
	{
		return;
	}
	sub_system->AddMappingContext(this->m_inputMappingContext, 0);
	// 显示鼠标
	this->SetShowMouseCursor(true);
	this->ChangeMouseEvent(true);

	const FVector default_location(0, 0, 0);
	this->m_movePointCircleInstance = Cast<AMovePointCircle>(world->SpawnActor(this->m_movePointCircleClass, &default_location, nullptr));
	this->m_movePointCircleInstance->Hide();
}

void AWorldPawnController::MoveAction(const FInputActionValue& _value)
{
	auto pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("pawn nullptr, in MoveAction"));
		return;
	}
	const auto movement_vector = _value.Get<FVector2D>();

	const FRotator rotation = this->GetControlRotation();
	const FRotator yaw_rotation(0, rotation.Yaw, 0);
	const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
	const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
	pawn->AddMovementInput(forward_direction, movement_vector.Y);
	pawn->AddMovementInput(right_direction, movement_vector.X);
}

void AWorldPawnController::MouseMoveAction(const FInputActionValue& _value)
{
	if(this->bEnableMouseOverEvents)
	{
		return;
	}
	const auto look_vector = _value.Get<FVector2D>() * this->m_mouseSensitivity;
	// 仅支持横向
	this->AddYawInput(look_vector.X);
}

void AWorldPawnController::MouseRollAction(const FInputActionValue& _value)
{
	const auto value = _value.Get<float>() * this->m_mouseRollSensitivity;
	
	auto pawn = this->GetPawn();
	if (pawn == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("pawn nullptr, in MouseRollAction"));
		return;
	}
	Cast<AWorldPawn>(pawn)->CameraMove(value);
	//const FRotator rotation = this->GetControlRotation();
	//const FVector forward_direction = FRotationMatrix(rotation).GetUnitAxis(EAxis::X);
	//// pawn->AddMovementInput(forward_direction, value);
	//pawn->AddActorLocalOffset(forward_direction * value);
}

void AWorldPawnController::MouseClickAction(const FInputActionValue& _value)
{
	FHitResult hit_result;
	if(GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, hit_result))
	{
		const auto impact_point = hit_result.ImpactPoint;
		auto world = GetWorld();
		auto high_light_actor = Cast<ICheckInterface>(hit_result.GetActor());
		// auto world_person = Cast<AWorldPersonCharacter>(hit_result.GetActor());
		// GetActorNameOrLabel获取编辑器中自定义名称
		if(this->m_movementCharacter == nullptr)
		{
			UE_LOG(WordPawnController, Warning, TEXT("movementCharacter nullptr, in moveLeftAction"));
			return;
		}

		if(this->m_movePointCircleClass == nullptr)
		{
			UE_LOG(WordPawnController, Warning, TEXT("point circle nullptr, on moveLeftAction"));
			return;
		}
		/*if(world_person != nullptr)
		{
			if (this->m_checkedActor != nullptr)
			{
				this->m_checkedActor->Check(false);
			}
			return;
		}*/
		if (high_light_actor != nullptr)
		{
			// 不是地图
			if(this->m_checkedActor != nullptr)
			{
				this->m_checkedActor->Check(false);
			}
			
			this->m_checkedActor = high_light_actor;
			this->m_checkedActor->Check(true);
			return;
			// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("not map"));
		}else
		{
			this->m_movePointCircleInstance->ShowInLocation(impact_point);
			if (this->m_checkedActor != nullptr)
			{
				this->m_checkedActor->Check(false);
				this->m_checkedActor = nullptr;
			}
		}
		// 移动
		// 获取当前位置
		FVector current_location = this->m_movementCharacter->GetActorLocation();
		AAIController* movement_controller = this->m_movementCharacter->GetController<AAIController>();
		// c->MoveToActor(_actor, _radius);
		/*FAIMoveRequest MoveReq;
		MoveReq.SetUsePathfinding(true);
		MoveReq.SetAcceptanceRadius(5);
		MoveReq.SetReachTestIncludesAgentRadius(false);
		MoveReq.SetGoalLocation(impact_point);
		MoveReq.SetNavigationFilter(movement_controller->GetDefaultNavigationFilterClass());
		movement_controller->MoveTo(MoveReq);*/
		// movement_controller->MoveToLocation(impact_point, -1, true, true, false, false);
		movement_controller->MoveToLocation(impact_point);
		// 需要导航网格体
		// Cast<AAIController>(this->m_movementCharacter->Controller)->MoveTo()
		// 这里AIController底层调用了MoveTo 本质还是寻路
		//constexpr float acceptance_radius = -1; // 距离目标点小于该值则认为到达目标点
		//constexpr bool stop_on_overlap = true; // 是否将pawn的范围加到上面参数中
		//constexpr bool use_path_finding = true; // 是否使用寻路
		//constexpr bool project_destination_to_navigation = false;
		//constexpr bool can_strafe = true; // 是否采用标志
		//const TSubclassOf<UNavigationQueryFilter> filter_class = nullptr;
		//constexpr bool allow_partial_paths = true; // 无法到达目标时使用不完整路径，即无法到达目标时会到达最接近的点
		//auto result = Cast<AAIController>(this->m_movementCharacter->Controller)->MoveToLocation(FVector(impact_point.X, impact_point.Y, current_location.Z)
		//	, acceptance_radius, stop_on_overlap, use_path_finding, project_destination_to_navigation, can_strafe, filter_class, allow_partial_paths);
	}else
	{
		// GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("not"));
	}
}

void AWorldPawnController::SpaceAction(const FInputActionValue& _value)
{
	const auto character_location = this->m_movementCharacter->GetActorLocation();
	const FVector forward_direction = FRotationMatrix(this->GetControlRotation()).GetUnitAxis(EAxis::X);
	auto pawn = Cast<AWorldPawn>(this->GetPawn());
	if(pawn != nullptr)
	{
		// Cast<AAIController>(pawn->Controller)->MoveToLocation(character_location);
		pawn->MoveToLocation(character_location - forward_direction * pawn->GetSpaceMovementOffset());
	}
}

void AWorldPawnController::SpaceStartAction(const FInputActionValue& _value)
{
	this->m_movementCharacter->BeginSpace();
}

void AWorldPawnController::SpaceEndAction(const FInputActionValue& _value)
{
	this->m_movementCharacter->EndSpace();
}

void AWorldPawnController::Key1Action(const FInputActionValue& _value)
{
	AWorldGameMode* gameMode = Cast<AWorldGameMode>(this->GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->SetTimeDilation(0.0);
	}
	/*auto func = this->m_widget->FindFunction(FName("PauseButtonClick"));
	if (func == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("PauseButtonClickFunciton nullptr, in Action"));
		return;
	}
	this->m_widget->ProcessEvent(func, nullptr);*/
}

void AWorldPawnController::Key2Action(const FInputActionValue& _value)
{
	AWorldGameMode* gameMode = Cast<AWorldGameMode>(this->GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->SetTimeDilation(1.0);
	}
	//auto func = this->m_widget->FindFunction(FName("OneButtonClick"));
	//if (func == nullptr)
	//{
	//	UE_LOG(WordPawnController, Warning, TEXT("OneButtonClickFunciton nullptr, in Action"));
	//	return;
	//}
	//this->m_widget->ProcessEvent(func, nullptr);
}

void AWorldPawnController::Key3Action(const FInputActionValue& _value)
{
	AWorldGameMode* gameMode = Cast<AWorldGameMode>(this->GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->SetTimeDilation(2.0);
	}
	/*auto func = this->m_widget->FindFunction(FName("TwoButtonClick"));
	if (func == nullptr)
	{
		UE_LOG(WordPawnController, Warning, TEXT("TwoButtonClickFunciton nullptr, in Action"));
		return;
	}
	this->m_widget->ProcessEvent(func, nullptr);*/
}

void AWorldPawnController::MouseRightStartAction(const FInputActionValue& _value)
{
	this->ChangeMouseEvent(false);
}

void AWorldPawnController::MouseRightEndAction(const FInputActionValue& _value)
{
	this->ChangeMouseEvent(true);
}

void AWorldPawnController::ChangeMouseEvent(const bool _enable)
{
	this->bEnableMouseOverEvents = _enable;
	this->bEnableClickEvents = _enable;
}
