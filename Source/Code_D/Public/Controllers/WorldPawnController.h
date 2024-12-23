// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldPawnController.generated.h"

class AWorldPersonCharacter;
class ICheckInterface;
class AMovePointCircle;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UClass;
class UActorInfoViewWidget;
/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(WordPawnController, Log, All);

UCLASS()
class CODE_D_API AWorldPawnController : public APlayerController
{
	GENERATED_BODY()

public:
	AWorldPawnController();
	virtual void SetupInputComponent() override;

	virtual void EndPlay(const EEndPlayReason::Type _endPlayReason) override;

	void ShowActorInfoView(const FText& _text) const;

	void HideActorInfoView() const;

	void MoveToActor(AActor* _actor, const float _radius) const;

	UFUNCTION(BlueprintCallable)
	void SetMovementCharacter(AWorldPersonCharacter* _movementPersonCharacter);

protected:
	virtual void BeginPlay() override;
	void MoveAction(const FInputActionValue& _value);
	void MouseMoveAction(const FInputActionValue& _value);
	void MouseRollAction(const FInputActionValue& _value);
	void MouseClickAction(const FInputActionValue& _value);
	void SpaceAction(const FInputActionValue& _value);
	void SpaceStartAction(const FInputActionValue& _value);
	void SpaceEndAction(const FInputActionValue& _value);
	void Key1Action(const FInputActionValue& _value);
	void Key2Action(const FInputActionValue& _value);
	void Key3Action(const FInputActionValue& _value);
	void MouseRightStartAction(const FInputActionValue& _value);
	void MouseRightEndAction(const FInputActionValue& _value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "sensitivity", ScriptName = "mouseSensitivity", ToolTip = "修改鼠标灵敏度"))
	float m_mouseSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "mouse roll sensitivity", ScriptName = "mouseRollSensitivity", ToolTip = "修改鼠标滚轮灵敏度"))
	float m_mouseRollSensitivity = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Data", meta = (DisplayName = "movement pawn", ToolTip = "移动的目标"))
	TObjectPtr<AWorldPersonCharacter> m_movementCharacter = nullptr;

private:
	void ChangeMouseEvent(const bool _enable);

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(DisplayName="inputMappingContext"))
	TObjectPtr<UInputMappingContext> m_inputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "move action"))
	TObjectPtr<UInputAction> m_moveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "mouse move action"))
	TObjectPtr<UInputAction> m_mouseMoveAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "mouse roll action"))
	TObjectPtr<UInputAction> m_mouseRollAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "mouse click action"))
	TObjectPtr<UInputAction> m_mouseClickAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "space action"))
	TObjectPtr<UInputAction> m_spaceAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "key 1 action"))
	TObjectPtr<UInputAction> m_key1Action = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "key 2 action"))
	TObjectPtr<UInputAction> m_key2Action = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "key 2 action"))
	TObjectPtr<UInputAction> m_key3Action = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (DisplayName = "mouse right action"))
	TObjectPtr<UInputAction> m_mouseRight = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (AllowedClasses = "MovePointCircle", DisplayName="move point circle class"), Category = "movementCharacter")
	TObjectPtr<UClass> m_movePointCircleClass = nullptr;

	TObjectPtr<AMovePointCircle> m_movePointCircleInstance = nullptr;
	ICheckInterface* m_checkedActor = nullptr;
};
