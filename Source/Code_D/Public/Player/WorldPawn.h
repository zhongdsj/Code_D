// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WorldPawn.generated.h"

class UTimelineComponent;
class UFloatingPawnMovement;
class UCameraComponent;

UCLASS()
class CODE_D_API AWorldPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWorldPawn();

	// Called every frame
	virtual void Tick(float _deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;

	void SetCameraFov(const float _fov);

	void CameraMove(const float _value);

	float GetSpaceMovementOffset() const;

	void MoveToLocation(const FVector& _location);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "camera fov", ToolTip = "相机fov"))
	float m_cameraFov = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "space movement offset length", ToolTip = "按下空格时，pawn与movement character相对距离"))
	float m_spaceMovementOffset = 2300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "threshold value for move distance", ToolTip = "平滑移动，timeline从0开始的最小距离"))
	float m_distanceThresholdValue = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "threshold value for play rate", ToolTip = "平滑移动，距离小于阈值时 play rate"))
	float m_playRateThresholdValue = 5.0f;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player Camera")
	TObjectPtr<UCameraComponent> m_cameraComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	TObjectPtr<UFloatingPawnMovement> m_movementComponent = nullptr;

	// UPROPERTY(EditDefaultsOnly, Category = "camera move timeline")
	TObjectPtr<UTimelineComponent> m_cameraMoveTimeLineComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "camera move timeline")
	TObjectPtr<UCurveFloat> m_timelineCurve = nullptr;

	float m_cameraMove = 0.0f;

	FVector m_moveFrom = { 0, 0, 0 };
	FVector m_moveTo = { 0, 0, 0 };

	void CameraMoveTimelineTickCallBack(const float _value);
	void CameraMoveTimelineFinishCallBack();
};
