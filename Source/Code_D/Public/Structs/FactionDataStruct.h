# pragma once
# include "CoreMinimal.h"
# include "Structs/BaseDataStruct.h"
# include "FactionDataStruct.generated.h"

struct FPersonDataStruct;

USTRUCT(Blueprintable)
struct FFactionDataStruct : public FBaseDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "faction_name", ToolTip = "势力名称"))
	FString faction_name = "default";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "owner handle", ToolTip = "势力拥有者"))
	FDataTableRowHandle owner_handle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "faction_background", ToolTip = "势力背景图片"))
	TObjectPtr<UTexture2D> faction_background;

	FFactionDataStruct();

	FPersonDataStruct* owner_data = nullptr;

	virtual void Pack() override;
};
