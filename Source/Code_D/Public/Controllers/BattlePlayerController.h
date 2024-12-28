// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePlayerController.generated.h"

class ABattleCharacter;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(BattlePlayerController, Log, All);
UCLASS()
class CODE_D_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	ABattleCharacter* GetBattleCharacter() const;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveAction(const FInputActionValue& _value);
	void LookAction(const FInputActionValue& _value);
	void ViewAction(const FInputActionValue& _value);
	void JumpAction(const FInputActionValue& _value);
	void MouseLeftAction(const FInputActionValue& _value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "sensitivity", ScriptName = "mouseSensitivity", ToolTip = "修改鼠标灵敏度"))
	float m_mouseSensitivity = 1.0f;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> m_inputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_gamePlayerMove = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_gamePlayerLook = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_gamePlayerView = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_gamePlayerJump = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> m_gamePlayerMouseLeft = nullptr;
};
