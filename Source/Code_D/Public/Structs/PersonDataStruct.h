# pragma once
# include "CoreMinimal.h"
#include "BaseDataStruct.h"
# include "Structs/PersonBaseDataStruct.h"
# include "PersonDataStruct.generated.h"

struct FFactionDataStruct;

USTRUCT(Blueprintable)
struct FPersonDataStruct : public FBaseDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "person_name", ToolTip = "人物名称"))
	FString person_name = "default";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "faction handle", ToolTip = "所属势力"))
	FDataTableRowHandle faction_handle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "person data", ToolTip = "人物属性"))
	FPersonBaseDataStruct person_data;

	FFactionDataStruct* faction_data = nullptr;
	// FPersonDataStruct() = default;
	// explicit FPersonDataStruct(const FPersonBaseDataStruct* _base): person_data(*_base) {};

	virtual void Pack() override;
};
