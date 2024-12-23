// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataComponent.generated.h"

struct FBaseDataStruct;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODE_D_API UDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	static FName GetTag();
	
	// Sets default values for this component's properties
	UDataComponent();

	FName GetDataName() const;

	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;
	virtual void InitializeComponent() override;
	virtual FString GetDetails() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "data", DisplayName = "data handle", ToolTip = "数据"))
	FDataTableRowHandle m_dataHandle;
	FBaseDataStruct* m_data = nullptr;
};
