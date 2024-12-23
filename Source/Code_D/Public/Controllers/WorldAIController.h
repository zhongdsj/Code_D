// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "WorldAIController.generated.h"

/**
 * 
 */
UCLASS()
class CODE_D_API AWorldAIController : public AAIController
{
	// todo UCrowdFollowingComponent源码 重写避障逻辑
	GENERATED_BODY()
public:
	virtual void Tick(float _deltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID _requestID, const FPathFollowingResult& _result) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "data")
	float m_voLength = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "data")
	bool m_useAvoid = false;
private:
	bool m_lookAtActor = true;
	bool m_avoid = false;
	FVector m_endLocation;
};
