// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovePointCircle.generated.h"

class UCircleComponent;

UCLASS()
class CODE_D_API AMovePointCircle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovePointCircle();
	// Called every frame
	virtual void Tick(float _deltaTime) override;
	
	UFUNCTION()
	void OverlappingBattleCharacter(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

	void ShowInLocation(const FVector& _location);

	void Hide();

	float GetAliveTime() const;

	void SetVisibility(const bool _visibility);

	virtual void EndPlay(const EEndPlayReason::Type _endPlayReason) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "circle alive time", ToolTip = "存活时间, 0表示持续显示直到目标到达"))
	float m_aliveTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "offset by location", ToolTip = "生成位置与实际位置offset"))
	FVector m_offset = { 0, 0, 10 };
private:
	FTimerHandle* m_timeHandle = nullptr;
};
