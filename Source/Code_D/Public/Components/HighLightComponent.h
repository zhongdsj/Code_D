// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HighLightComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(HighLightComponent, Log, All);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODE_D_API UHighLightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHighLightComponent();

	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void BeginMouseHover() const;
	void EndMouseHover() const;
	void HighLight(const bool _show) const;

	UPROPERTY(EditDefaultsOnly, Category = "Materia")
	TObjectPtr<UMaterialInterface> m_highLightMaterialInterface = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", meta = (DisplayName = "high light mesh name", ToolTip = "高亮mesh名称"))
	FString m_highLightMeshName = "";
	
private:
	UMeshComponent* m_mesh = nullptr;
};
