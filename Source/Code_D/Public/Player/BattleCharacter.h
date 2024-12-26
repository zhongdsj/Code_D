// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Enums/WeaponAnimationEnum.h"
#include "GameFramework/Character.h"
#include "BattleCharacter.generated.h"

class UBattleComponent;
class AMovePointCircle;
class USpringArmComponent;
struct FInputActionValue;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CODE_D_API ABattleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABattleCharacter();

	virtual void Tick(float _deltaTime) override;

	void BeginHighLight();
	void EndHighLight();

	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;

	UBattleComponent* GetBattleComponent() const;

	void BattleDirectionChange(const FVector2D& _input) const;

	void ChangeSpringArmLength(const bool _change) const;

	UFUNCTION(BlueprintCallable)
	void UpAttack();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "show circle", ToolTip = "是否显示圆圈"))
	bool m_showCircle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "show high light", ToolTip = "是否显示高亮"))
	bool m_showHighLight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "circle color", ToolTip = "圆环颜色"))
	FColor m_circleColor = { 0, 184, 255 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "circle radius", ToolTip = "颜色光晕范围"))
	float m_circleRadius = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Circle"))
	TObjectPtr<UStaticMeshComponent> m_circle = nullptr;
private:
	UPROPERTY(EditDefaultsOnly, Category="Player Camera")
	TObjectPtr<UCameraComponent> m_cameraComponent;

	UPROPERTY(EditDefaultsOnly, Category="Camera Boom")
	TObjectPtr<USpringArmComponent> m_springArmComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Materia")
	TObjectPtr<UMaterialInterface> m_highLightMaterialInterface = nullptr;

	TSoftObjectPtr<UBattleComponent> m_battleComponent = nullptr;
};
