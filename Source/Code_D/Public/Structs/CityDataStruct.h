# pragma once
# include "CoreMinimal.h"
# include "Structs/BaseDataStruct.h"
# include "CityDataStruct.generated.h"

struct FPersonDataStruct;

USTRUCT(Blueprintable)
struct FCityDataStruct : public FBaseDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "name", ToolTip = "城池名称"))
	FString city_name = "default";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "loyalty", ToolTip = "忠诚度"))
	float loyalty = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "prosperity", ToolTip = "繁荣度"))
	float prosperity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "security", ToolTip = "治安度"))
	float security = 0.0f;

	// 蓝图只支持uint8与int32
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "owner handle", ToolTip = "所有者"))
	FDataTableRowHandle owner_handle;

	FPersonDataStruct* owner_data = nullptr;

	// 打包函数，将handle取出放入data中
	virtual void Pack() override;
};
