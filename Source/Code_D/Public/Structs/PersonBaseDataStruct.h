# pragma once
# include "CoreMinimal.h"
# include "Engine/DataTable.h"
# include "PersonBaseDataStruct.generated.h"

USTRUCT(Blueprintable)
struct FPersonBaseDataStruct : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "health", ToolTip = "生命值"))
	float health = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "stamina", ToolTip = "耐力,影响动作"))
	float stamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "strength", ToolTip = "力量,影响伤害"))
	float strength = 0.0f;
	// 熟练度影响对应出招速度与冷却
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Proficiency with long poles", ToolTip = "长杆熟练度"))
	float long_poles_proficiency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "one_handed proficiency", ToolTip = "单手熟练度"))
	float one_handed_proficiency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "two_handed proficiency", ToolTip = "双手熟练度"))
	float two_handed_proficiency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "archery proficiency", ToolTip = "弓箭熟练度"))
	float archery_proficiency = 0.0f;
};
