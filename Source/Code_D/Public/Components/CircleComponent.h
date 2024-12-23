// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "CircleComponent.generated.h"

/**
 * 
 */
UCLASS()
class CODE_D_API UCircleComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UCircleComponent();

	UFUNCTION()
	void OverlappingBattleCharacter(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComp, int32 _otherBodyIndex, bool _bFromSweep, const FHitResult& _sweepResult);

protected:
	virtual void BeginPlay() override;
	void BeginMouseHover();
	void EndMouseHover();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "circle color", ToolTip = "圆环颜色"))
	FColor m_circleColor = { 0, 184, 255 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "overlap hide", ToolTip = "重叠隐藏"))
	bool m_overlapHide = false;
};
